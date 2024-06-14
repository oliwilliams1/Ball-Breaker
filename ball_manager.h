#ifndef BALL_MANAGER_H
#define BALL_MANAGER_H
#include "vec2.h"
#include <vector>
#include "cell_manager.h"

class BallMan
{
private:
    struct BallStruct
    {
        vec2 pos;
        vec2 vel;
    };

	std::vector<BallStruct> balls;
	SDL_Renderer* renderer;
    SDL_Texture* ballTexture;
    SDL_Texture* ballRedTexture;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int radius = 10;

    CellMan* cellManager;

public:
    BallMan(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, CellMan* cellManager) : renderer(renderer), SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT), cellManager(cellManager) {
        ballTexture = renderCircleToTexture(renderer, SDL_Color{ 255, 255, 255, 255 });
        ballRedTexture = renderCircleToTexture(renderer, SDL_Color{ 255, 0, 0, 255 });
    }

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

    SDL_Texture* renderCircleToTexture(SDL_Renderer* renderer, SDL_Color colour) {
        // Create a square texture with a size of 2 * radius
        int size = 2 * radius;
        SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size, size);

        // Set the texture as the render target
        SDL_SetRenderTarget(renderer, texture);

        // Clear the texture
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        // Draw the circle
        SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
        for (int x = -radius; x <= radius; x++) {
            for (int y = -radius; y <= radius; y++) {
                if (x * x + y * y <= radius * radius) {
                    SDL_RenderDrawPoint(renderer, x + radius, y + radius);
                }
            }
        }

        // Reset the render target to the default
        SDL_SetRenderTarget(renderer, NULL);

        return texture;
    }

    void draw()
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < balls.size(); i++)
        {
            int x = (int)balls[i].pos.x;
            int y = (int)balls[i].pos.y;

            CellCollisionData collisionData = cellManager->getCollisionData(x, y);
            
            //bool collision = data.collided;

            SDL_Rect dstrect = { x - 10, y - 10, 20, 20 };
            SDL_RenderCopy(renderer, (collisionData.collided ? ballRedTexture : ballTexture), NULL, &dstrect);
        }
    }

    void destroy()
	{
		SDL_DestroyTexture(ballTexture);
	}
};

#endif /* BALL_MANAGER_H */