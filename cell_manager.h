#ifndef CELL_MANAGER_H
#define CELL_MANAGER_H

#include "block.h"

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

	TextureData renderHealth(const char* health)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, health, colour);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		return { texture, surface->w, surface->h };
	}

	void addCell(int x, int y, int health) 
	{
		cells[x][y].active = true;
		cells[x][y].health = health;
		cells[x][y].textureData = renderHealth(std::to_string(health).c_str());
	}

	int clamp(int value, int min, int max) { // swag clamp func
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

	CellCollisionData getCollisionData(int ball_x, int ball_y)
	{
		int radius = 10;
		int cell_x = ball_x / x_scale;
		int cell_y = ball_y / y_scale;

		for (int x = -1; x < 2; x++)
		{
			int _x = clamp(cell_x + x, 0, x_size - 1);
			if (_x < 0 || _x >= x_size) continue;

			for (int y = -1; y < 2; y++)
			{
				int _y = clamp(cell_y + y, 0, y_size - 1);
				if (_y < 0 || _y >= y_size) continue;

				if (cells[_x][_y].active)
				{
					int cellPos_x = cells[_x][_y].rect.x;
					int cellPos_y = cells[_x][_y].rect.y;
					int cellScale_x = cells[_x][_y].rect.w;
					int cellScale_y = cells[_x][_y].rect.h;

					// find the nearest point on the cell to the ball via clamp function
					int nearest_x = clamp(ball_x, cellPos_x, cellPos_x + cellScale_x - 1);
					int nearest_y = clamp(ball_y, cellPos_y, cellPos_y + cellScale_y - 1);

					int distance = abs(nearest_x - ball_x) + abs(nearest_y - ball_y);
					if (distance <= radius)
					{
						SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
						SDL_RenderDrawLine(renderer, ball_x, ball_y, nearest_x, nearest_y);
						SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
						return { true, (nearest_x - ball_x) > 0 };
					}
				}
			}
		}
		return { false, false };
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