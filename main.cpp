#include <iostream>
#include <sstream>
#include <cstring>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "swag_utils.h"
#include "colours.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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

    window = SDL_CreateWindow("Ball Breaker!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    TTF_Font* font = TTF_OpenFont("Font/segment.ttf", 24);
    
    bool isRunning = true;

    while (isRunning) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        clearScreen(renderer, black);

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

        SDL_RenderPresent(renderer);
    }

    // Destory because cool
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}