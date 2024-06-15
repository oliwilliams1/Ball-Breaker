#include "ball_breaker.h"

int main(int argc, char* args[]) {
    bool debug = true;
	BallBreaker game(debug = debug);

    while (game.isRunning)
    {
		game.run();
    }

    game.destroy();
	return 0;
}