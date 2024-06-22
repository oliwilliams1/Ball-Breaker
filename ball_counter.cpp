#include "ball_counter.h"

ballCounter::ballCounter(SDL_Renderer* renderer, TTF_Font* font, vec2* ballPos)
{
	this->renderer = renderer;
	this->font = font;
	this->ballPos = ballPos;
}

void ballCounter::renderNew()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	surface = TTF_RenderText_Solid(font, "1", { 255, 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	savedBallPos = *ballPos;
}

void ballCounter::draw()
{
	if (ballPos->x != savedBallPos.x || ballPos->y != savedBallPos.y) {
		renderNew();
	}
	SDL_Rect destinationRect = { ballPos->x + 24, ballPos->y - 12, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
}

void ballCounter::destroy()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}