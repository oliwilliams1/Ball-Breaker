#include "streak_renderer.h"
#include "mat2.h"

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

	transformArrows();
}

void streakMan::constructArrow()
{
	int sizeOfArrowVerts = sizeof(arrowVerts) / sizeof(arrowVerts[0]);
	vec2 downVec = vec2(0, 1);
	arrowVerts[0] = vec2(0, 0); // Center
	arrowVerts[1] = vec2(0, -11); // Up
	arrowVerts[2] = vec2(15, 5); // Right
	arrowVerts[3] = vec2(-15, 5); // Left
	arrowVerts[4] = arrowVerts[2] + downVec * 10; // RightDown
	arrowVerts[5] = arrowVerts[3] + downVec * 10; // LeftDown

	for (int i = 0; i < sizeOfArrowVerts; i++)
	{
		arrowVerts[i] = arrowVerts[i];
	}
}

void streakMan::renderTrajectory(vec2* arrowVerts[6])
{
	const std::vector<SDL_Vertex> verts =
	{
		{ SDL_FPoint{arrowVerts[0]->x, arrowVerts[0]->y}, SDL_Color{255, 255, 255, 255}, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[1]->x, arrowVerts[1]->y}, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
		{ SDL_FPoint{arrowVerts[2]->x, arrowVerts[2]->y}, SDL_Color{255, 255, 255, 255}, SDL_FPoint{0},},
		
		{ SDL_FPoint{arrowVerts[0]->x, arrowVerts[0]->y}, SDL_Color{255, 255, 255, 255}, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[1]->x, arrowVerts[1]->y}, SDL_Color{255, 255, 255, 255}, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[3]->x, arrowVerts[3]->y}, SDL_Color{255, 255, 255, 255}, SDL_FPoint{0},},

		{ SDL_FPoint{arrowVerts[2]->x, arrowVerts[2]->y}, SDL_Color{255, 255, 255, 255}, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[4]->x, arrowVerts[4]->y}, SDL_Color{255, 255, 255, 255}, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[0]->x, arrowVerts[0]->y}, SDL_Color{255, 255, 255, 255}, SDL_FPoint{0},},

		{ SDL_FPoint{arrowVerts[3]->x, arrowVerts[3]->y}, SDL_Color{255, 255, 255, 255}, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[5]->x, arrowVerts[5]->y}, SDL_Color{255, 255, 255, 255}, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[0]->x, arrowVerts[0]->y}, SDL_Color{255, 255, 255, 255}, SDL_FPoint{0},},

	};

	SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
}

void streakMan::transformArrows()
{
	static float angle = 0.0f;
	angle += 0.001f;
	mat2 scale(1.0f, 0.0f,
			   0.0f, 1.0f);

	mat2 rotation(cos(angle), -sin(angle),
			      sin(angle), cos(angle));

	mat2 combinedMatrix = scale * rotation;

	vec2 transformedArrowVerts[6];
	for (int i = 0; i < 6; i++)
	{
		transformedArrowVerts[i] = arrowVerts[i] * combinedMatrix;
	}

	vec2* temp[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = &transformedArrowVerts[i];
	}
	renderTrajectory(temp);	
}

streakMan::streakMan(SDL_Renderer* renderer, vec2* ballSpawnPos, BallMan* ballManager) {
	this->renderer = renderer;
	this->fromPos = ballSpawnPos;
	this->ballManager = ballManager;
	constructArrow();
};