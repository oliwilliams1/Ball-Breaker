#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <sstream>
#include <cstring>
#include "vec2.h"
class Cell
{
private:
	int x;
	int y;
	int w = 50;
	int h = 50;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect rect = { x, y, w, h };
	SDL_Color colour = { 255, 255, 255, 255 };
	bool fill = false;
	TTF_Font* font = nullptr;

public:
	int health;

	Cell(int x, int y, int health, SDL_Color colour) : x(x), y(y), health(health), colour(colour) {};

	void initRenderer(SDL_Renderer* renderer, TTF_Font* font) {
		this->renderer = renderer;
		this->font = font;
	}


	void draw() {
		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
		if (fill) {
			SDL_RenderFillRect(renderer, &rect);
		}
		else {
			SDL_RenderDrawRect(renderer, &rect);
		}
		SDL_Surface* surface = TTF_RenderText_Solid(font, std::to_string(health).c_str(), colour);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_Rect destinationRect = { x + 17, y + 14, surface->w, surface->h };
		SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
	}

};

#endif