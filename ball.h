#ifndef BALL_H
#define BALL_H
#include "vec2.h"

class Ball
{
private:
	vec2 position;
	vec2 velocity;
	float radius;
    SDL_Renderer* renderer;

public:
	Ball(vec2 position, vec2 velocity, float radius, SDL_Renderer* renderer) : position(position), velocity(velocity), radius(radius), renderer(renderer) {}
	Ball() : position(0, 0), velocity(0, 0), radius(0), renderer(nullptr) {}
	
	void init(vec2 position, vec2 velocity, float radius, SDL_Renderer* renderer)
	{
		this->position = position;
		this->velocity = velocity;
		this->radius = radius;
		this->renderer = renderer;
	}
	void update(float dt, int SCREEN_WIDTH, int SCREEN_HEIGHT)
	{
		position += velocity * dt;
		if (position.x - radius < 0) {
			position.x = radius;
			velocity.x = -velocity.x;
		}
		if (position.x + radius > SCREEN_WIDTH) {
			position.x = SCREEN_WIDTH - radius;
			velocity.x = -velocity.x;
		}
		if (position.y - radius < 0) {
			position.y = radius;
			velocity.y = -velocity.y;
		}
		if (position.y + radius > SCREEN_HEIGHT) {
			position.y = SCREEN_HEIGHT - radius;
			velocity.y = -velocity.y;
		}
	}

	void draw()
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < radius; i++) {
            int cx = 0;
            int cy = i;
            int df = 1 - i;
            int d_e = 3;
            int d_se = -2 * i + 5;
            int x = (int)position.x; // should be float but warnings flow in
            int y = (int)position.y;
            while (cx <= cy) {
                SDL_RenderDrawLine(renderer, x + cx, y + cy, x - cx, y + cy);
                SDL_RenderDrawLine(renderer, x + cx, y - cy, x - cx, y - cy);
                SDL_RenderDrawLine(renderer, x + cy, y + cx, x - cy, y + cx);
                SDL_RenderDrawLine(renderer, x + cy, y - cx, x - cy, y - cx);

                if (df < 0) {
                    df += d_e;
                    d_e += 2;
                    d_se += 2;
                }
                else {
                    df += d_se;
                    d_e += 2;
                    d_se += 4;
                    cy--;
                }
                cx++;
            }
        }
	}
};
#endif // BALL_H