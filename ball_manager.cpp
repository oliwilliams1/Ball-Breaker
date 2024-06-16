#include "ball_breaker.h"

void BallMan::renderCircleToTexture(SDL_Renderer* renderer, int radius)
{
    // Create a texture to fit bounds of circle
    int size = 2 * radius;
    SDL_Surface* surface = SDL_CreateRGBSurface(0, size, size, 32,
        0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    if (!surface) {
        std::cerr << "SDL_CreateRGBSurface failed: " << SDL_GetError() << std::endl;
        return;
    }

    Uint32* pixels = (Uint32*)surface->pixels; // Get the pixel array

    // Fill surface with a white circle
    for (int y = -radius; y < radius; ++y) {
        for (int x = -radius; x < radius; ++x) {
            if (x * x + y * y <= radius * radius) { // Check if the point is inside the circle
                pixels[(y + radius) * surface->w + (x + radius)] = 0xFFFFFFFF; // Set the pixel color with full alpha
            }
        }
    }

    // Create a texture from the surface
    ballTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (ballTexture == nullptr) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
    }

    // Free surface
    SDL_FreeSurface(surface);
}

void BallMan::addBall(vec2 pos, vec2 vel)
{
    BallStruct ball;
    ball.pos = pos;
    ball.vel = vel;
    balls.push_back(ball);
}

void BallMan::update(float dt)
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

void BallMan::draw()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < balls.size(); i++)
    {
        cellManager->collisionTest(&balls[i]);

        SDL_Rect dstrect = { (int)balls[i].pos.x - 10, (int)balls[i].pos.y - 10, 20, 20 };

        SDL_RenderCopy(renderer, ballTexture, nullptr, &dstrect);
    }
}

void BallMan::destroy()
{
    SDL_DestroyTexture(ballTexture);
}

BallMan::BallMan(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, CellMan* cellManager) :
                renderer(renderer),
                SCREEN_WIDTH(SCREEN_WIDTH),
                SCREEN_HEIGHT(SCREEN_HEIGHT),
                cellManager(cellManager) 
{
    renderCircleToTexture(renderer, 10);
}