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
	CellStruct cells[11][11]; // 10x10 2d array
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color colour = { 255, 255, 255, 255 };

public:
	CellMan(SDL_Renderer* renderer, TTF_Font* font) : renderer(renderer), font(font)
	{	
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 11; j++) {
				cells[i][j].rect = { i * 50, j * 50, 50, 50 };
			}
		}		
	}

	TextureData renderHealth(const char* health)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, health, colour);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		//SDL free surface here?
		return { texture, surface->w, surface->h };
	}

	void addCell(int x, int y, int health) 
	{
		cells[x][y].active = true;
		cells[x][y].health = health;
		cells[x][y].textureData = renderHealth(std::to_string(health).c_str());
	}

	void draw() 
	{
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 11; j++) {
				if (cells[i][j].active) {
					SDL_RenderDrawRect(renderer, &cells[i][j].rect);
					SDL_Rect destRect = { i * 50 + ((cells[i][j].health < 10) ? 13 : 3), j * 50 + 9, cells[i][j].textureData.x, cells[i][j].textureData.y};
					SDL_RenderCopy(renderer, cells[i][j].textureData.texture, NULL, &destRect);
				}
			}
		}
	}
};

#endif /* CELL_MANAGER_H */