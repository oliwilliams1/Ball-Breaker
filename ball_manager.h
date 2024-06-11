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

    void renderFilledCircle(SDL_Surface* surface, int x, int y, int radius, Uint32 color) 
    {
        for (int dy = -radius; dy <= radius; dy++) {
            int dx = (int)sqrt(radius * radius - dy * dy);
            for (int px = x - dx; px <= x + dx; px++) {
                Uint32* pixel = (Uint32*)((Uint8*)surface->pixels + (y + dy) * surface->pitch + px * sizeof(Uint32));
                *pixel = color;
            }
        }
    }

    SDL_Texture* renderCircleToTexture(SDL_Renderer* renderer, SDL_Color _color)
    {
        int radius = 10;
        
        int surfaceWidth = 2 * radius, surfaceHeight = 2 * radius;
        SDL_Surface* surface = SDL_CreateRGBSurface(0, radius * 2, radius * 2, 32, 0, 0, 0, 0);

        Uint32 color = SDL_MapRGBA(surface->format, _color.r, _color.g, _color.b, _color.a);
        renderFilledCircle(surface, radius, radius, radius, color);

        SDL_Texture* circleTexture = SDL_CreateTextureFromSurface(renderer, surface);

        //SDL_FreeSurface(surface);

        return circleTexture;
    }

    void draw()
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < balls.size(); i++)
        {
            int x = (int)balls[i].pos.x;
            int y = (int)balls[i].pos.y;

            bool collision = cellManager->isPointInCell(x, y);

            SDL_Rect dstrect = { x - 10, y - 10, 20, 20 };
            SDL_RenderCopy(renderer, (collision) ? ballRedTexture : ballTexture, NULL, &dstrect);
        }
    }

    void destroy()
	{
		SDL_DestroyTexture(ballTexture);
	}
};

#endif /* BALL_MANAGER_H */