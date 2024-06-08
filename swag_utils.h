#ifndef SWAG_UTILS_H
#define SWAG_UTILS_H
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "block.h"

void clearScreen(SDL_Renderer* renderer, SDL_Color colour);

void drawRect(SDL_Renderer* renderer, int x_pos, int y_pos, int width, int height, SDL_Color colour, bool fill);

void drawFilledCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color);

void drawCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color);

void drawText(SDL_Renderer* renderer, int x, int y, const char * text, SDL_Color colour, TTF_Font* font);

#endif // SWAG_UTILS_H