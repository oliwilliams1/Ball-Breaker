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
		{ SDL_FPoint{ mousePos.x,           mousePos.y},              SDL_Color{ 255, 255, 255, 180 }, SDL_FPoint{ 0 }, },
		{ SDL_FPoint{ fromPos->x - cross.x,  fromPos->y - cross.y},   SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
		{ SDL_FPoint{ fromPos->x + cross.x,  fromPos->y + cross.y },  SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
	};

	// Render as triangle
	SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0);

	transformArrows(direction);
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

void streakMan::renderTrajectory(vec2* arrowVerts[6], SDL_Color colour)
{
	// Construct verts from pointer, 4 triangles
	const std::vector<SDL_Vertex> verts =
	{
		{ SDL_FPoint{arrowVerts[0]->x, arrowVerts[0]->y}, colour, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[1]->x, arrowVerts[1]->y}, colour, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[2]->x, arrowVerts[2]->y}, colour, SDL_FPoint{0},},
		
		{ SDL_FPoint{arrowVerts[0]->x, arrowVerts[0]->y}, colour, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[1]->x, arrowVerts[1]->y}, colour, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[3]->x, arrowVerts[3]->y}, colour, SDL_FPoint{0},},

		{ SDL_FPoint{arrowVerts[2]->x, arrowVerts[2]->y}, colour, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[4]->x, arrowVerts[4]->y}, colour, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[0]->x, arrowVerts[0]->y}, colour, SDL_FPoint{0},},

		{ SDL_FPoint{arrowVerts[3]->x, arrowVerts[3]->y}, colour, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[5]->x, arrowVerts[5]->y}, colour, SDL_FPoint{0},},
		{ SDL_FPoint{arrowVerts[0]->x, arrowVerts[0]->y}, colour, SDL_FPoint{0},},

	};

	SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
}

float clampFunc(float x, float fac)
{
	//     floors them for sharp sin wave thing     FAC is default distance between arrows
	return ((x / 10.0f - floor(x / 10.0f) + 0.5f) * fac) - 12.0f;
}

void streakMan::transformArrows(vec2 direction)
{
	for (int arrowInt = 0; arrowInt < 6; arrowInt++)
	{
		float fac = 30.0f;
		// Destination of the arrow
		vec2 destination(*fromPos + (direction * (arrowInt * fac + clampFunc(*time / 100.0f, fac))));

		float distance = sqrt((destination.x - fromPos->x) * (destination.x - fromPos->x) + (destination.y - fromPos->y) * (destination.y - fromPos->y));

		// Scale based on how far the arrow is
		float scaleFactor = 0.65f * (1.0f - distance / 200.0f);

		// Rotate based on launch dir
		float angle = atan2(direction.x, direction.y) + M_PI;

		// Generate correct matricies for transformations
		mat2 scale(scaleFactor,  0.0f,
				   0.0f, scaleFactor);

		mat2 rotation(cos(angle), -sin(angle),
			sin(angle), cos(angle));

		// Apply rotation first, then scale
		mat2 combinedMatrix = scale * rotation;

		// Apply transformation and store in temp array
		vec2 transformedArrowVerts[6];
		for (int i = 0; i < 6; i++)
		{
			transformedArrowVerts[i] = arrowVerts[i] * combinedMatrix;
		}

		// Translate verts
		for (int i = 0; i < 6; i++)
		{
			transformedArrowVerts[i] += destination;
		}

		// Temp pointers because im stupid
		vec2* temp[6];
		for (int i = 0; i < 6; i++)
		{
			temp[i] = &transformedArrowVerts[i];
		}

		// Render the darn thing
		renderTrajectory(temp, SDL_Color{ 255, 255, 255, static_cast<Uint8>(255 * (1 - (arrowInt * 0.1f))) });
	}
}

void streakMan::bringDownArrow(vec2 pos)
{
	SDL_Color colour = { 255, 255, 255, 255 };
	const std::vector<SDL_Vertex> verts =
	{
		{ SDL_FPoint{pos.x + 10.0f, pos.y},         colour, SDL_FPoint{0},},
		{ SDL_FPoint{pos.x + 15.0f, pos.y},         colour, SDL_FPoint{0},},
		{ SDL_FPoint{pos.x + 10.0f, pos.y + 20.0f}, colour, SDL_FPoint{0},},

		{ SDL_FPoint{pos.x + 15.0f, pos.y},         colour, SDL_FPoint{0},},
		{ SDL_FPoint{pos.x + 10.0f, pos.y + 20.0f}, colour, SDL_FPoint{0},},
		{ SDL_FPoint{pos.x + 15.0f, pos.y + 20.0f}, colour, SDL_FPoint{0},},

		{ SDL_FPoint{pos.x + 2.0f,  pos.y + 20.0f}, colour, SDL_FPoint{0},},
		{ SDL_FPoint{pos.x + 23.0f, pos.y + 20.0f}, colour, SDL_FPoint{0},},
		{ SDL_FPoint{pos.x + 12.5f, pos.y + 30.0f}, colour, SDL_FPoint{0},},

	};

	SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
}

streakMan::streakMan(SDL_Renderer* renderer, vec2* ballSpawnPos, BallMan* ballManager, Uint64* time) {
	this->time = time;
	this->renderer = renderer;
	this->fromPos = ballSpawnPos;
	this->ballManager = ballManager;
	constructArrow();
};