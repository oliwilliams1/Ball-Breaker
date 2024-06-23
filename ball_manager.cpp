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
    ball.isInAnimation = false;
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
        if (balls[i].pos.x + radius > screenDimensions->x) {
            balls[i].pos.x = screenDimensions->x - radius;
            balls[i].vel.x = -balls[i].vel.x;
        }
        if (balls[i].pos.y - radius < 0) {
            balls[i].pos.y = radius;
            balls[i].vel.y = -balls[i].vel.y;
        }
        if (balls[i].pos.y + radius > screenDimensions->y) {
            balls[i].pos.y = screenDimensions->y - radius;
            balls[i].vel.y = -balls[i].vel.y;
        }
    }
}

void BallMan::checkIfOutOfBounds()
{
    for (int i = 0; i < balls.size(); i++) {
        if (balls[i].pos.y > ballSpawnPos.y && balls[i].isInAnimation == false) {
            balls[i].isInAnimation = true;
            balls[i].vel = vec2(-(balls[i].pos.x - ballSpawnPos.x), 0);
            balls[i].vel = balls[i].vel.normalize() * 500.0f;
        }
        if (balls[i].isInAnimation && abs(ballSpawnPos.x - balls[i].pos.x) < 2) {
            balls.erase(balls.begin() + i);
            *ballsRecieved = *ballsRecieved + 1;
            std::cout << *ballsRecieved << std::endl;
        }
    }
}

void BallMan::draw()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Balls in game
    for (int i = 0; i < balls.size(); i++)
    {
        cellManager->collisionTest(&balls[i]);

        SDL_Rect dstrect = { (int)balls[i].pos.x - 10, (int)balls[i].pos.y - 10, 20, 20 };

        SDL_RenderCopy(renderer, ballTexture, nullptr, &dstrect);
    }
}

void BallMan::drawCenterBall()
{
    // Center ball
    SDL_Rect dstrect = { ballSpawnPos.x - 10, ballSpawnPos.y - 10, 20, 20 };
    SDL_RenderCopy(renderer, ballTexture, nullptr, &dstrect);
}

void BallMan::drawTrajectory(vec2* direction, vec2* origPos)
{
    int r = 10;
    for (int i = 0; i < 10; i++)
    {
        SDL_Rect dstrect = {
        origPos->x + (i * 30) * direction->x - r + i,
        origPos->y + (i * 30) * direction->y - r + i,
        (r - i) * 2,
        (r - i) * 2,
        };

		SDL_RenderCopy(renderer, ballTexture, nullptr, &dstrect);
    }
}

void BallMan::destroy()
{
    SDL_DestroyTexture(ballTexture);
}

BallMan::BallMan(SDL_Renderer* renderer, vec2* screenDimensions, CellMan* cellManager, int* ballsRecieved) :
                renderer(renderer),
                screenDimensions(screenDimensions),
                cellManager(cellManager),
                ballsRecieved(ballsRecieved)
{
    renderCircleToTexture(renderer, 10);
    ballSpawnPos = vec2(screenDimensions->x / 2, screenDimensions->y - 100);
}