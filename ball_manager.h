#pragma once

#include "vec2.h"
#include <vector>
#include "cell_manager.h"
#include "swag_utils.h"

class BallMan
{
private:
	std::vector<BallStruct> balls;
	SDL_Renderer* renderer;
    SDL_Texture* ballTexture;
    SDL_Texture* ballRedTexture;
    vec2* screenDimensions;
    int radius = 10;
    CellMan* cellManager;
    int* ballsRecieved;

public:
    vec2 ballSpawnPos;

    void renderCircleToTexture(SDL_Renderer* renderer, int radius);

    BallMan(SDL_Renderer* renderer, vec2* screenDimensions, CellMan* cellManager, int* ballsRecieved);

    void addBall(vec2 pos, vec2 vel);

    void update(float dt);  

    void checkIfOutOfBounds();

    void drawTrajectory(vec2* direction, vec2* origPos);

    void draw();

    void drawCenterBall();

    void destroy();
};