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

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 800;

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        printf("TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    window = SDL_CreateWindow("Ball Buster!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetWindowAlwaysOnTop(window, SDL_TRUE);
    SDL_SetWindowAlwaysOnTop(window, SDL_FALSE);

    TTF_Font* font = TTF_OpenFont("Font/segment.ttf", 32);
    
    bool isRunning = true;

    Uint64 previousTime = 0;
    float deltaTime = 0.0f;

    CellMan CellManager(renderer, font, SCREEN_WIDTH, SCREEN_HEIGHT, true);

    CellManager.addCell(5, 5, 55);

    BallMan BallManager(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, &CellManager);
    BallManager.draw();

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(-500, 500);

    vec2 ballPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100);

    for (int i = 0; i < 10; i++) {
        BallManager.addBall(ballPos, vec2(dis(gen), dis(gen)));
    }


    while (isRunning) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 100 milliseconds = 0.1 seconds
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        /* debug draw
        for (int i = 0; i < 10; i++) {
            drawText(renderer, (i * 25) + 60, (i * 25) + 60, std::to_string(i).c_str(), white, font);
        }

        drawText(renderer, SCREEN_WIDTH - 220, 10, "Score: 0", white, font);

        drawRect(renderer, 10, 10, 10, 10, white, true);
        drawRect(renderer, 20, 20, 10, 10, red, false);
        drawRect(renderer, 30, 30, 10, 10, green, true);
        drawRect(renderer, 40, 40, 10, 10, blue, false);
        drawFilledCircle(renderer, 60, 200, 50, yellow);
        drawCircle(renderer, 200, 60, 50, red);
        */
        //std::cout << "FPS = " << 1.0f / deltaTime << std::endl;

        clearScreen(renderer, black);
        BallManager.update(deltaTime);
        BallManager.draw();

        CellManager.draw();

        SDL_RenderPresent(renderer);

        Uint64 currentTime = SDL_GetTicks64();
        deltaTime = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;
    }

    // Destory because cool
    BallManager.destroy();
    CellManager.destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}