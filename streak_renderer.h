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

	vec2 arrowVerts[6];
	vec2 transformedArrowVerts[6];

public:
	streakMan(SDL_Renderer* renderer, vec2* ballSpawnPos, BallMan* ballManager);

	void constructArrow();

	void renderTrajectory(vec2* arrowVerts[6]);

	void transformArrows();

	void renderStreak(vec2 mousePos);
};