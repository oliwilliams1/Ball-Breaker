#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <sstream>
#include <cstring>
#include "vec2.h"
#include "swag_utils.h"

class Cell
{
private:
    int w = 50;
    int h = 50;
    SDL_Renderer* renderer = nullptr;
    SDL_Rect rect = { x, y, w, h };
    SDL_Color colour = { 255, 255, 255, 255 };
    bool fill = false;
    TTF_Font* font = nullptr;
	SDL_Surface* surface;
	SDL_Texture* texture;

public:
	int x;
	int y;
    int health;

    Cell(int _x, int _y, int _health, SDL_Color _colour, SDL_Renderer* _renderer, TTF_Font* _font)
        : x(_x), y(_y), health(_health), colour(_colour), renderer(_renderer), font(_font)
    {
        rect = { x, y, w, h };
		renderHealth();
    }

	void renderHealth() {
		surface = TTF_RenderText_Solid(font, std::to_string(health).c_str(), colour);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
	}

	void draw() {
		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
		if (fill) {
			SDL_RenderFillRect(renderer, &rect);
		}
		else {
			SDL_RenderDrawRect(renderer, &rect);
		}
		
		SDL_Rect destinationRect = { x + 13, y + 9, surface->w, surface->h }; // position image where i want it
		SDL_RenderCopy(renderer, texture, NULL, &destinationRect); // place image on screen
	}
};

#endif