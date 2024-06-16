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
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int radius = 10;

    CellMan* cellManager;

public:
    void renderCircleToTexture(SDL_Renderer* renderer, int radius);

    BallMan(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, CellMan* cellManager);

    void addBall(vec2 pos, vec2 vel);

    void update(float dt);  

    void draw();

    void destroy();
};