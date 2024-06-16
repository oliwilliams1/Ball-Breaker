#pragma once
#include <SDL.h>
#include "vec2.h"
#include <vector>

class streakMan
{
private:
	SDL_Renderer* renderer = nullptr;
	vec2 origPos;
	vec2 mousePos;
	float radius = 10;

public:
	streakMan(SDL_Renderer* renderer) : renderer(renderer) {};

	void renderStreak(vec2 fromPos, vec2 mousePos);
};