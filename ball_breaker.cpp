#include "ball_breaker.h"

CellMan* BallBreaker::createCellMan(SDL_Renderer* renderer, TTF_Font* font, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool debug = true)
{
    return new CellMan(renderer, font, SCREEN_WIDTH, SCREEN_HEIGHT, debug);
}

BallMan* BallBreaker::createBallMan(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, CellMan* CellManager)
{
    return new BallMan(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, CellManager);
}

streakMan* BallBreaker::createStreakMan(SDL_Renderer* renderer, float radius)
{
    return new streakMan(renderer);
}

void BallBreaker::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    if (TTF_Init() < 0) {
        printf("TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
    }

    window = SDL_CreateWindow("Ball Buster!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    SDL_SetWindowAlwaysOnTop(window, SDL_TRUE);
    SDL_SetWindowAlwaysOnTop(window, SDL_FALSE);

    // Enable alpha blending for the renderer
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    font = TTF_OpenFont("Font/segment.ttf", 32);

    CellManager = createCellMan(renderer, font, SCREEN_WIDTH, SCREEN_HEIGHT, debug);
    CellManager->addCell(5, 5, 55);

    BallManager = createBallMan(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, CellManager);
    BallManager->draw();

    streakManager = createStreakMan(renderer, 10.0f);

    if (debug) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dis(-500, 500);

        vec2 ballPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100);

        for (int i = 0; i < 10; i++) {
            BallManager->addBall(ballPos, vec2(dis(gen), dis(gen)));
        }
    }
}

void BallBreaker::captureEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT) {
            isRunning = false;
        }
    }

    buttons = SDL_GetMouseState(&x, &y);
}

void BallBreaker::update()
{
    BallManager->update(deltaTime);
}

void BallBreaker::updateDeltaTime()
{
    currentTime = SDL_GetTicks64();
    deltaTime = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;
}

void BallBreaker::render() 
{
    clearScreen(renderer, { 0, 0, 0, 255 });

    BallManager->draw();
    CellManager->draw();
    streakManager->renderStreak(vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100), vec2(x, y));

    SDL_RenderPresent(renderer);
}
void BallBreaker::run()
{
    captureEvents();
    update();
    render();
    updateDeltaTime();
}

void BallBreaker::destroy()
{
    BallManager->destroy();
    CellManager->destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}