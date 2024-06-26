#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "vec2.h"
class ballCounter
{
private:
	SDL_Surface* surface;
	SDL_Texture* texture;
	TTF_Font* font;
	SDL_Renderer* renderer;
	vec2* ballPos;

public:
	ballCounter(SDL_Renderer* renderer, TTF_Font* font, vec2* ballPos);

	void renderNew(int ballsNum);

	void draw();

	void destroy();
};