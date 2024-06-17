#include "streak_renderer.h"

void streakMan::renderStreak(vec2 mousePos)
{
	vec2 direction = *fromPos - mousePos;

	// Normalize
	direction = direction.normalize();

	// Cross
	vec2 cross = vec2(direction.y, -direction.x);

	// Scale vector to radius of ball
	cross *= radius;

	// Vertex Data
	const std::vector<SDL_Vertex> verts = 
	{
		{ SDL_FPoint{ mousePos.x,           mousePos.y},            SDL_Color{ 255, 255, 255, 180 }, SDL_FPoint{ 0 }, },
		{ SDL_FPoint{ fromPos->x - cross.x,  fromPos->y - cross.y},   SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
		{ SDL_FPoint{ fromPos->x + cross.x,  fromPos->y + cross.y },  SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
	};

	// Render as triangle
	SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
}