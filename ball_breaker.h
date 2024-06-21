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
    vec2 screenDimensions = vec2(500, 800);
    bool debug;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    CellMan* CellManager;
    BallMan* BallManager;
    streakMan* streakManager;
    Uint64 previousTime;
    Uint64 currentTime;
    float deltaTime;

    int x, y;
    Uint32 buttons;

    CellMan* createCellMan(SDL_Renderer* renderer, TTF_Font* font, vec2* screenDimensions, bool debug);
    BallMan* createBallMan(SDL_Renderer* renderer, vec2* screenDimensions, CellMan* CellManager);
    streakMan* createStreakMan(SDL_Renderer* renderer, float radius, vec2* ballSpawnPos, Uint64* time);
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