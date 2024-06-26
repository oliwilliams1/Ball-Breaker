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
#include "ball_counter.h"
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
    ballCounter* ballCounterManager;
    Uint64 previousTime;
    Uint64 currentTime;
    float deltaTime;
    int ballsNum = 20;
    int ballsAdded = 0;
    int oldBallsRecieved = 0;
    int ballsRecieved = 0;
    bool readyToShoot = true;
    bool renderTrajectory = true;
    Uint64 timeLastShot;
    float timeBetweenShots = 0.1f;
    bool shooting = false;
    vec2 mouseVec;
    vec2 bringDownButtonPos = vec2(screenDimensions.x - 60, screenDimensions.y - 60);

    int x, y;
    Uint32 buttons;

    CellMan* createCellMan(SDL_Renderer* renderer, TTF_Font* font, vec2* screenDimensions, bool debug);
    BallMan* createBallMan(SDL_Renderer* renderer, vec2* screenDimensions, CellMan* CellManager, int* ballsRecieved);
    streakMan* createStreakMan(SDL_Renderer* renderer, float radius, vec2* ballSpawnPos, Uint64* time);
    ballCounter* createBallCounterManager(SDL_Renderer* renderer, TTF_Font* font, vec2* ballPos);
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