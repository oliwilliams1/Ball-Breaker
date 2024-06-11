#ifndef BALL_MANAGER_H
#define BALL_MANAGER_H
#include "vec2.h"
#include <vector>

struct BallStruct
{
	vec2 pos;
	vec2 vel;
};

class BallMan
{
private:
	std::vector<BallStruct> balls;
	SDL_Renderer* renderer;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int radius = 10;

public:
    BallMan(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT) : renderer(renderer), SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT) {}

    void addBall(vec2 pos, vec2 vel)
    {
        BallStruct ball;
        ball.pos = pos;
        ball.vel = vel;
        balls.push_back(ball);
    }

    void update(float dt)
    {

		for (int i = 0; i < balls.size(); i++) {
			balls[i].pos += balls[i].vel * dt;
            if (balls[i].pos.x - radius < 0) {
                balls[i].pos.x = radius;
                balls[i].vel.x = -balls[i].vel.x;
            }
            if (balls[i].pos.x + radius > SCREEN_WIDTH) {
                balls[i].pos.x = SCREEN_WIDTH - radius;
                balls[i].vel.x = -balls[i].vel.x;
            }
            if (balls[i].pos.y - radius < 0) {
                balls[i].pos.y = radius;
                balls[i].vel.y = -balls[i].vel.y;
            }
            if (balls[i].pos.y + radius > SCREEN_HEIGHT) {
                balls[i].pos.y = SCREEN_HEIGHT - radius;
                balls[i].vel.y = -balls[i].vel.y;
            }
		}
    }

    void draw()
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < balls.size(); i++) {
            int x = (int)balls[i].pos.x;
            int y = (int)balls[i].pos.y;

            for (int i = 0; i < radius; i++) {
                int cx = 0;
                int cy = i;
                int df = 1 - i;
                int d_e = 3;
                int d_se = -2 * i + 5;

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
    }
};

#endif /* BALL_MANAGER_H */