#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;


	game = new Game();

	game->init("Star Strike", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 30*32 + 150, 20*32 + 100, false);

	while (game->running()) {

		frameStart = SDL_GetTicks();


		game->eventHandler();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	
	game->clean();

	return 0;

}