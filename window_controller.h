#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_H
#include <SDL.h>
#include <SDL_ttf.h>

void initWindow(SDL_Window** window, SDL_Renderer** renderer, TTF_Font** font, int SCREEN_WIDTH, int SCREEN_HEIGHT);

#endif /* WINDOW_CONTROLLER_H */