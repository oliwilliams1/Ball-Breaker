#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "block.h"

struct renderData
{
	SDL_Renderer* renderer;
	TTF_Font* font;
};

struct BallStruct
{
    vec2 pos;
    vec2 vel;
};

void clearScreen(SDL_Renderer* renderer, SDL_Color colour);

void drawRect(SDL_Renderer* renderer, int x_pos, int y_pos, int width, int height, SDL_Color colour, bool fill);

void drawFilledCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color);

void drawCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color);

void drawText(SDL_Renderer* renderer, int x, int y, const char * text, SDL_Color colour, TTF_Font* font);