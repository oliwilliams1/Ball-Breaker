#ifndef BALL_H
#define BALL_H
#include "vec2.h"

class Ball
{
public:
	vec2 position;
	vec2 velocity;
	float radius;

	Ball(vec2 position, vec2 velocity, float radius) : position(position), velocity(velocity), radius(radius) {}

	void update(float dt)
	{
		position += velocity * dt;
	}
};
#endif // BALL_H