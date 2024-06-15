#ifndef STREAK_RENDERER_H
#define STREAK_RENDERER_H

#include <SDL.h>
#include "vec2.h"

void renderStreak(SDL_Renderer* renderer, vec2 origPos, vec2 mousePos, float radius);

#endif /* STREAK_RENDERER_H */