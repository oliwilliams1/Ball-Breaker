#include <SDL.h>
#include "streak_renderer.h"
#include "vec2.h"
#include <vector>

void renderStreak(SDL_Renderer* renderer, vec2 origPos, vec2 mousePos, float radius)
{
	vec2 dir = origPos - mousePos;

	// Normalize
	dir = dir.normalize();

	// Cross
	vec2 cross = vec2(dir.y, -dir.x);

	// Scale vector to radius of ball
	cross *= radius;

	// Vertex data
	const std::vector<SDL_Vertex> verts =
	{
		{ SDL_FPoint{ mousePos.x,           mousePos.y},            SDL_Color{ 255, 255, 255, 180 }, SDL_FPoint{ 0 }, },
		{ SDL_FPoint{ origPos.x - cross.x,  origPos.y - cross.y},   SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
		{ SDL_FPoint{ origPos.x + cross.x,  origPos.y + cross.y },  SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
	};
	// Render as triangle
	SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
}
