#include "ball_breaker.h"

CellMan* BallBreaker::createCellMan(SDL_Renderer* renderer, TTF_Font* font, vec2* screenDimensions, bool debug = true)
{
    return new CellMan(renderer, font, screenDimensions, debug);
}

BallMan* BallBreaker::createBallMan(SDL_Renderer* renderer, vec2* screenDimensions, CellMan* CellManager)
{
    return new BallMan(renderer, screenDimensions, CellManager);
}

streakMan* BallBreaker::createStreakMan(SDL_Renderer* renderer, float radius, vec2* ballSpawnPos, Uint64* time)
{
    return new streakMan(renderer, ballSpawnPos, BallManager, time);
}

ballCounter* BallBreaker::createBallCounterManager(SDL_Renderer*, TTF_Font*, vec2* ballPos)
{
	return new ballCounter(renderer, font, ballPos);
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

    window = SDL_CreateWindow("Ball Buster!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenDimensions.x, screenDimensions.y, SDL_WINDOW_SHOWN);
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

    CellManager = createCellMan(renderer, font, &screenDimensions, debug);
    CellManager->addCell(5, 5, 55);

    BallManager = createBallMan(renderer, &screenDimensions, CellManager);
    BallManager->draw();

    streakManager = createStreakMan(renderer, 10.0f, &BallManager->ballSpawnPos, &currentTime);

    ballCounterManager = createBallCounterManager(renderer, font, &BallManager->ballSpawnPos);
    ballCounterManager->renderNew();

    if (debug) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dis(-500, 500);

        vec2 ballPos(screenDimensions.x / 2, screenDimensions.y - 100);
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

        if (e.type == SDL_MOUSEBUTTONDOWN) {
            vec2 mouseVec = BallManager->ballSpawnPos - vec2(x, y);
            mouseVec = mouseVec.normalize();
            mouseVec *= 500.0f;
            BallManager->addBall(BallManager->ballSpawnPos, mouseVec);
        }
    }

    buttons = SDL_GetMouseState(&x, &y);
}

void BallBreaker::update()
{
    BallManager->checkIfOutOfBounds();
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
    streakManager->renderStreak(vec2(x, y));
    ballCounterManager->draw();

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
    TTF_CloseFont(font);
    BallManager->destroy();
    CellManager->destroy();
    ballCounterManager->destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}