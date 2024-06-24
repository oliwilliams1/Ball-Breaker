#pragma once

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
	CellMan(SDL_Renderer* renderer, TTF_Font* font, vec2* screenDimensions, bool debug = false) : renderer(renderer), font(font)
	{	
		x_scale = screenDimensions->x / x_size;
		y_scale = screenDimensions->y / y_size;
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

	int renderHealth(CellStruct* cell);

	void addCell(int x, int y, int health);

	int clamp(int value, int min, int max);

	void removeHealth(CellStruct* cell);

	int collisionTest(BallStruct* ball);

	void draw();

	void destroy();
};