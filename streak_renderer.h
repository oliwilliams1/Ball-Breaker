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
	vec2* fromPos;

public:
	streakMan(SDL_Renderer* renderer, vec2* ballSpawnPos) : renderer(renderer), fromPos(ballSpawnPos) {};

	void renderStreak(vec2 mousePos);
};