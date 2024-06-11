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

	bool isPointInCell(int x, int y)
	{
		x /= x_scale;
		y /= y_scale;

		if (x >= 0 && x < x_size && y >= 0 && y < y_size)
		{
			if (cells[x][y].active)
				return true;

			for (int _y = y - 1; _y <= y + 1; _y++)
			{
				for (int _x = x - 1; _x <= x + 1; _x++)
				{
					// skip the current cell
					if (_x == x && _y == y)
						continue;

					// check if the neighboring cell is within the window bounds
					if (_x >= 0 && _x < x_size && _y >= 0 && _y < y_size)
					{
						if (cells[_x][_y].active)
							return true;
					}
				}
			}
		}

		return false;
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