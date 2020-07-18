#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "TileMap.h"
#include "ECS.h"
#include "Components.h"

GameObject* player;
TileMap* map;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager;
auto& newPlayer(manager.addEntity());

Game::Game()
{

}

Game::~Game()
{
}

void Game::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems initialized..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created..." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			std::cout << "Renderer created..." << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}


	player = new GameObject("assets/body_03.png", 0, 0);
	map = new TileMap();

	newPlayer.addComponent<PositionComponent>();
	
}

void Game::eventHandler()
{
	

	SDL_PollEvent(&event);
	
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:

		break;
	default:
		break;
	}
}

void Game::update()
{
	player->Update();
	manager.update();
	std::cout << newPlayer.getComponent<PositionComponent>().x() << "," << newPlayer.getComponent<PositionComponent>().y() << std::endl;
}

void Game::render()
{
		SDL_RenderClear(renderer);
		map->drawMap();
		player->Render();
		SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned..." << std::endl;
}

bool Game::running()
{
	return isRunning;
}
