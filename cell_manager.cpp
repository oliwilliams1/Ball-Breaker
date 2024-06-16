#include "cell_manager.h"

int CellMan::renderHealth(CellStruct* cell)
{
	if (cell->textureData.texture != NULL or !cell->active) {
		SDL_DestroyTexture(cell->textureData.texture);
	}
	if (!cell->active) return 1;

	SDL_Surface* surface = TTF_RenderText_Solid(font, std::to_string(cell->health).c_str(), colour);
	cell->textureData.texture = SDL_CreateTextureFromSurface(renderer, surface);
	cell->textureData.x = surface->w;
	cell->textureData.y = surface->h;
	SDL_FreeSurface(surface);
	return 0;
}

void CellMan::addCell(int x, int y, int health)
{
	cells[x][y].active = true;
	cells[x][y].health = health;
	renderHealth(&cells[x][y]);
}

int CellMan::clamp(int value, int min, int max)
{
	if (value < min) {
		return min;
	}
	else if (value > max) {
		return max;
	}
	else {
		return value;
	}
}

void CellMan::removeHealth(CellStruct* cell)
{
	cell->health--;
	if (cell->health <= 0) {
		cell->active = false;
	}
	renderHealth(cell);
}

void CellMan::collisionTest(BallStruct* ball)
{
	int radius = 10;
	int cell_x = ball->pos.x / x_scale;
	int cell_y = ball->pos.y / y_scale;

	// Iterate horizontally on 3x3 grid
	for (int x = -1; x < 2; x++)
	{
		int _x = clamp(cell_x + x, 0, x_size - 1);
		if (_x < 0 || _x >= x_size) continue;

		// Iterate vertically on 3x3 grid
		for (int y = -1; y < 2; y++)
		{
			int _y = clamp(cell_y + y, 0, y_size - 1);
			if (_y < 0 || _y >= y_size) continue;

			if (cells[_x][_y].active)
			{
				// Use clamp function on both dimensions to find closest point on cell to the ball
				float nearest_x = clamp(ball->pos.x, cells[_x][_y].rect.x, cells[_x][_y].rect.x + cells[_x][_y].rect.w - 1);
				float nearest_y = clamp(ball->pos.y, cells[_x][_y].rect.y, cells[_x][_y].rect.y + cells[_x][_y].rect.h - 1);

				// Calculate distance
				float dx = ball->pos.x - nearest_x;
				float dy = ball->pos.y - nearest_y;
				float distance = sqrt(dx * dx + dy * dy);

				// Check if distance is less than radius for collision reaction
				if (distance <= radius) {
					removeHealth(&cells[_x][_y]);
					// Adjust ball position to the nearest point on the cell + radius along vector direction
					ball->pos.x = nearest_x + (ball->pos.x - nearest_x) * (radius + 1) / (distance + 0.00001f);
					ball->pos.y = nearest_y + (ball->pos.y - nearest_y) * (radius + 1) / (distance + 0.00001f);

					// Adjust ball velocity based on what side of the cell the ball collided with
					if (abs((ball->pos.x - nearest_x)) < abs((ball->pos.y - nearest_y))) {
						ball->vel.y *= -1;
					}
					else {
						ball->vel.x *= -1;
					}
				}
			}
		}
	}
}

void CellMan::draw()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int x = 0; x < x_size; x++) {
		for (int y = 0; y < y_size; y++) {
			if (cells[x][y].active) {
				SDL_RenderDrawRect(renderer, &cells[x][y].rect);
				SDL_Rect destRect = { x * x_scale, y * y_scale, cells[x][y].textureData.x, cells[x][y].textureData.y };
				SDL_RenderCopy(renderer, cells[x][y].textureData.texture, NULL, &destRect);
			}
		}
	}
}

void CellMan::destroy()
{
	for (int x = 0; x < x_size; x++) {
		for (int y = 0; y < y_size; y++) {
			SDL_DestroyTexture(cells[x][y].textureData.texture);
		}
	}
}