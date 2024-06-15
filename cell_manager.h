#ifndef CELL_MANAGER_H
#define CELL_MANAGER_H

#include "block.h"
#include "swag_utils.h"

struct TextureData
{
	SDL_Texture* texture;
	int x;
	int y;
};

struct CellStruct
{
	bool active = false;
	int health;
	SDL_Rect rect;
	TextureData textureData;
};

struct CellCollisionData
{
	bool collided;
	bool axis; // 0 for x, 1 for y
};

class CellMan
{
private:
	CellStruct cells[10][16];
	int x_size = sizeof(cells) / sizeof(cells[0]);
	int y_size = sizeof(cells[0]) / sizeof(cells[0][0]);

	int x_scale;
	int y_scale;

	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color colour = { 255, 255, 255, 255 };

public:
	CellMan(SDL_Renderer* renderer, TTF_Font* font, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool debug = false) : renderer(renderer), font(font)
	{	
		x_scale = SCREEN_WIDTH / x_size;
		y_scale = SCREEN_HEIGHT / y_size;
		for (int i = 0; i < x_size; i++) {
			for (int j = 0; j < y_size; j++) {
				cells[i][j].rect = { i * x_scale, j * y_scale, x_scale, y_scale };
			}
		}
		if (debug) {
			addCell(0, 0, 0);
			for (int x = 0; x < x_size; x++) {
				addCell(x, 0, x);
			}

			for (int y = 0; y < y_size; y++) {
				addCell(0, y, y);
			}
		}
	}

	void renderHealth(CellStruct* cell)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, std::to_string(cell->health).c_str(), colour);
		cell->textureData.texture = SDL_CreateTextureFromSurface(renderer, surface);
		cell->textureData.x = surface->w;
		cell->textureData.y = surface->h;
		SDL_FreeSurface(surface);
	}

	void addCell(int x, int y, int health) 
	{
		cells[x][y].active = true;
		cells[x][y].health = health;
		renderHealth(&cells[x][y]);
	}

	int clamp(int value, int min, int max) { // Swag clamp function
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

	void removeHealth(CellStruct* cell)
	{
		cell->health--;
		if (cell->health <= 0) {
			cell->active = false;
		}
		renderHealth(cell);
	}

	void collisionTest(BallStruct* ball)
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
						} else {
							ball->vel.x *= -1;
						}
					}
				}
			}
		}
	}

	void draw() 
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

	void destroy()
	{
		for (int x = 0; x < x_size; x++) {
			for (int y = 0; y < y_size; y++) {
				SDL_DestroyTexture(cells[x][y].textureData.texture);
			}
		}
	}
};

#endif /* CELL_MANAGER_H */