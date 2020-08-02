#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Ship.h"
#include "TileMap.h"
#include "button.h"
#include <vector>

//#include "ECS.h"
//#include "Components.h"

//GameObject* player;
//GameObject* enemy;
Ship* player;
Ship* enemy;
Ship* player1;
Ship* enemy1;

Ship* temp = NULL;
Ship* active = NULL;

vector<Ship*> team1;
vector<Ship*> team2;

TileMap* map;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Button* fireButton;
Button* moveButton;

int turn = 0;

bool motion = false;

//Manager manager;
//auto& newPlayer(manager.addEntity());

Game::Game()
{

}

Game::~Game()
{
	//clean();
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

	

	fireButton = new Button("assets/FIRE.bmp", 64, 672, 128, 32);
	moveButton = new Button("assets/FIRE.bmp", 224, 672, 128, 32);
	ShipWeapon testWeapon(1,5,FiringArc(-45,45),8,DamageType(1.0f,1.0f));
	player = new Ship("NCC-1701", "Enterprise", 50, 50, 5, 20, 5, testWeapon, "assets/MushShipBlue.bmp", 0, 0);
	enemy = new Ship("KSS-1202", "K'Tinga", 50, 50, 5, 20, 5, testWeapon, "assets/MushShipRed.bmp", 200, 200);
	player1 = new Ship("NCC-6545", "Discovery", 50, 50, 5, 20, 5, testWeapon, "assets/MushShipBlue.bmp", 0, 64);
	enemy1 = new Ship("KSS-6969", "M'Lady", 50, 50, 5, 20, 5, testWeapon, "assets/MushShipRed.bmp", 200, 264);



	team1.push_back(player);
	team1.push_back(player1);
	team2.push_back(enemy);
	team2.push_back(enemy1);

	for (auto& enemy_ship : team2) {
		enemy_ship->setFacingLeft();
		enemy_ship->changeAngle(-90);
	}

	
	
	//player = new GameObject("assets/MushShipBlue.png", 0, 0);
	//enemy = new GameObject("assets/MushShipRed.png", 200, 200);
	map = new TileMap();

	//newPlayer.addComponent<PositionComponent>();
	
}

void Game::eventHandler()
{
	SDL_PollEvent(&event);
	//std::cout << event.button.x << ", " << event.button.y << std::endl;
	SDL_Point point = { event.button.x, event.button.y };
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		for (auto& ship : team1) {
			if (turn == 0 && SDL_PointInRect(&point, &ship->getBox())) {
				temp = ship;
				for (auto& ship : team1) {
					ship->setActive(false);
				}
				temp->setActive(true);
			}
		}
		for (auto& ship : team2) {
			if (turn == 1 && SDL_PointInRect(&point, &ship->getBox())) {
				temp = ship;
				for (auto& ship : team2) {
					ship->setActive(false);
				}
				temp->setActive(true);	
			}
		}
		/*if (turn == 1 && SDL_PointInRect(&point, &enemy->getBox())) {
			temp = enemy;
			temp->setActive(true);
		}*/
		if (turn == 0 && SDL_PointInRect(&point, &fireButton->getBox())) {
			turn = 1;
			player->AttackTarget(enemy, &(player->testWeapon));
			for (auto& ship : team1) {
				ship->setActive(false);
			}
		}
		else if (turn == 1 && SDL_PointInRect(&point, &moveButton->getBox())) {
			turn = 0;
			enemy->AttackTarget(player, &(enemy->testWeapon));
			for (auto& ship : team2) {
				ship->setActive(false);
			}
		}
		/*else {
			if (temp != NULL)
				temp->setActive(false);
			temp = NULL;
		}*/

		break;
	case SDL_MOUSEBUTTONUP:
		if (temp != NULL)
			//temp->setActive(false);
		temp = NULL;
		break;
	case SDL_MOUSEMOTION:
		if (temp != NULL && temp->getActive()) {
			temp->xpos = event.button.x;
			temp->ypos = event.button.y;
			temp->setLocation(floor(temp->getBox().x) / 32, floor(temp->getBox().y) / 32);
		}
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_SPACE:
			player->AttackTarget(enemy, &(player->testWeapon));
			break;
		case SDLK_a:
			enemy->AttackTarget(player, &(enemy->testWeapon));
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_SPACE:

			break;
		}
		break;

	default:
		break;
	}

}

void Game::update()
{
	//std::cout << "Motion: " << motion << std::endl;
	for (auto& player_ship : team1) {
		player_ship->Update();
	}
	for (auto& enemy_ship : team2) {
		enemy_ship->Update();
	}
	//player->Update();
	//enemy->Update();
	fireButton->Update();
	moveButton->Update();
	//RenderHPBar(384, 672, 128, 32, (float)(player->getHull() / 50), green, red);
	
	
	
	if (player->getHull() <= 0 || enemy->getHull() <= 0) {
		isRunning = false;  
	}
	//manager.update();
	//std::cout << newPlayer.getComponent<PositionComponent>().x() << "," << newPlayer.getComponent<PositionComponent>().y() << std::endl;
}  

void Game::render()
{	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	map->drawMap();
	for (auto& player_ship : team1) {
		player_ship->Render();
	}
	for (auto& enemy_ship : team2) {
		enemy_ship->Render();
	}
	//player->Render();
	//enemy->Render();
	if(turn == 0)
		fireButton->Render();
	if(turn == 1)
		moveButton->Render();
	//std::cout << player->getHull() << std::endl;
	//RenderHPBar(384, 672, 128, 32, (float)(player->getHull() / 50), green, red);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	std::cout << "Game cleaned..." << std::endl;
}

bool Game::running()
{
	return isRunning;
}

