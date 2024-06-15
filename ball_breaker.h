#pragma once

#include <iostream>
#include <sstream>
#include <cstring>
#include <random>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <thread>
#include "swag_utils.h"
#include "colours.h"
#include "vec2.h"
#include "cell_manager.h"
#include "ball_manager.h"
#include "streak_renderer.h"

class BallBreaker
{
private:
    const int SCREEN_WIDTH = 500;
    const int SCREEN_HEIGHT = 800;
    bool debug;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    CellMan* CellManager;
    BallMan* BallManager;
    Uint64 previousTime;
    Uint64 currentTime;
    float deltaTime;

    int x, y;
    Uint32 buttons;

    CellMan* createCellMan(SDL_Renderer* renderer, TTF_Font* font, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool debug);

    BallMan* createBallMan(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, CellMan* CellManager);

    void init();

public:
    bool isRunning = true;
    BallBreaker(bool debug = false) : debug(debug) { init(); }

    void captureEvents();

    void update();

    void updateDeltaTime();

    void render();

    void run();

    void destroy();
};