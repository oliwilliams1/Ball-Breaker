#pragma once
#include <SDL.h>
#include "vec2.h"
#include <vector>
#include "ball_manager.h"

class streakMan
{
private:
	BallMan* ballManager;
	SDL_Renderer* renderer = nullptr;
	vec2 origPos;
	vec2 mousePos;
	float radius = 10;
	vec2* fromPos;

public:
	streakMan(SDL_Renderer* renderer, vec2* ballSpawnPos, BallMan* ballManager) : renderer(renderer), fromPos(ballSpawnPos), ballManager(ballManager) {};

	void renderStreak(vec2 mousePos);
};