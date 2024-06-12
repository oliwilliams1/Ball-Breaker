#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include "swag_utils.h"
#include <SDL_ttf.h>
#include "block.h"

void clearScreen(SDL_Renderer* renderer, SDL_Color colour)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void drawRect(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color colour, bool fill)
{
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_Rect rect = { x, y, w, h };


	if (fill) {
		SDL_RenderFillRect(renderer, &rect);
	}
	else {
		SDL_RenderDrawRect(renderer, &rect);
	}
}

void drawFilledCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int i = 0; i < radius; i++) {
        int cx = 0;
        int cy = i;
        int df = 1 - i;
        int d_e = 3;
        int d_se = -2 * i + 5;

        while (cx <= cy) {
            SDL_RenderDrawLine(renderer, x + cx, y + cy, x - cx, y + cy);
            SDL_RenderDrawLine(renderer, x + cx, y - cy, x - cx, y - cy);
            SDL_RenderDrawLine(renderer, x + cy, y + cx, x - cy, y + cx);
            SDL_RenderDrawLine(renderer, x + cy, y - cx, x - cy, y - cx);

            if (df < 0) {
                df += d_e;
                d_e += 2;
                d_se += 2;
            }
            else {
                df += d_se;
                d_e += 2;
                d_se += 4;
                cy--;
            }
            cx++;
        }
    }
}

void drawCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int numPoints = 360; // Number of points to draw the circle
    double theta = 2 * M_PI / static_cast<double>(numPoints);

    for (int i = 0; i < numPoints; i++) {
        int x1 = static_cast<int>(x + radius * cos(i * theta));
        int y1 = static_cast<int>(y + radius * sin(i * theta));
        int x2 = static_cast<int>(x + radius * cos((i + 1) * theta));
        int y2 = static_cast<int>(y + radius * sin((i + 1) * theta));
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}

void drawText(SDL_Renderer* renderer, int x, int y, const char* text, SDL_Color colour, TTF_Font* font)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, colour);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect destinationRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
}

void clamp(int& val, int min, int max)
{
	if (val < min) {
		val = min;
	}
	else if (val > max) {
		val = max;
	}
}