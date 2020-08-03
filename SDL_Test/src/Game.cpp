#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Ship.h"
#include "TileMap.h"
#include "button.h"
#include "UIfunctions.h"
#include <vector>



//#include "ECS.h"
//#include "Components.h"

//GameObject* player;
//GameObject* enemy;

Ship* player;
Ship* player1;
Ship* player2;
Ship* player3;
Ship* enemy;
Ship* enemy1;
Ship* enemy2;
Ship* enemy3;

Ship* temp = NULL;
Ship* active = NULL;


vector<Ship*> blueTeam;
vector<Ship*> redTeam;

TileMap* map;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Surface* surf;
SDL_Texture* text;

Button* fireButton;
Button* moveButton;

string showText;

int turn = 0;

int gameCount = 0;
bool done = false;
string endText;

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

	IMG_Init(IMG_INIT_JPG);
	TTF_Init();

	fireButton = new Button("assets/FIRE.bmp", 64, 672, 128, 32);
	moveButton = new Button("assets/FIRE.bmp", 768, 672, 128, 32);
	ShipWeapon heavyWeapon(4,10,FiringArc(-45,45),12,DamageType(1.2f,1.0f));
	ShipWeapon smallWeapon(2, 5, FiringArc(-90, 90), 6, DamageType(0.9f, 1.1f));
	ShipWeapon snooperWeapon(8, 20, FiringArc(-20, 20), 30, DamageType(1.0f, 1.4f));
	player = new Ship("NCC-1701", "Enterprise", 50, 50, 6, 20, 5, heavyWeapon, "assets/MushShipBlue.bmp", 0, 256);
	player1 = new Ship("NCC-6545", "Discovery", 50, 50, 6, 20, 5, heavyWeapon, "assets/MushShipBlue.bmp", 0, 320);
	player2 = new Ship("NCC-4096", "Endeavour", 20, 40, 12, 10, 15, smallWeapon, "assets/RootedShipBlue.bmp", 0, 384);
	player3 = new Ship("NCC-8320", "Atlantis", 15, 10, 2, 50, -20, snooperWeapon, "assets/BoomBeatleBlue.bmp", 0, 64);

	enemy = new Ship("KSS-1202", "K'Tinga", 50, 50, 6, 20, 5, heavyWeapon, "assets/MushShipRed.bmp", 896, 256);
	enemy1 = new Ship("KSS-6969", "M'Lady", 50, 50, 6, 20, 5, heavyWeapon, "assets/MushShipRed.bmp", 896, 320);
	enemy2 = new Ship("KSS-4200", "Pepe Frog", 20, 40, 12, 10, 15, smallWeapon, "assets/RootedShipRed.bmp", 896, 384);
	enemy3 = new Ship("KSS-1337", "xX_SniperBug_Xx", 15, 10, 2, 50, -20, snooperWeapon, "assets/BoomBeatleRed.bmp", 896, 64);




	blueTeam.push_back(player);
	blueTeam.push_back(player1);
	blueTeam.push_back(player2);
	blueTeam.push_back(player3);
	redTeam.push_back(enemy);
	redTeam.push_back(enemy1);
	redTeam.push_back(enemy2);
	redTeam.push_back(enemy3);

	for (auto& enemy_ship : redTeam) {
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
		for (auto& ship : blueTeam) {
			if (turn == 0 && SDL_PointInRect(&point, &ship->getBox())) {
				temp = ship;
				active = ship;
				for (auto& ship : blueTeam) {
					ship->setActive(false);
				}
				temp->setActive(true);
			}
			else if (turn == 1 && SDL_PointInRect(&point, &ship->getBox())) {
				for (auto& ship : blueTeam) {
					ship->setTargeted(false);
				}
				ship->setTargeted(true);
			}
		}
		for (auto& ship : redTeam) {
			if (turn == 1 && SDL_PointInRect(&point, &ship->getBox())) {
				temp = ship;
				active = ship;
				for (auto& ship : redTeam) {
					ship->setActive(false);
				}
				temp->setActive(true);	
			}
			else if (turn == 0 && SDL_PointInRect(&point, &ship->getBox())) {
				for (auto& ship : redTeam) {
					ship->setTargeted(false);
				}
				ship->setTargeted(true);
			}
		}
		/*if (turn == 1 && SDL_PointInRect(&point, &enemy->getBox())) {
			temp = enemy;
			temp->setActive(true);
		}*/

		//Fire Button For Blue Team
		if (turn == 0 && SDL_PointInRect(&point, &fireButton->getBox())) {
			turn = 1;
			if (active != NULL) {
				for (auto& ship : redTeam) {
					if (ship->getTargeted()) {
						active->AttackTarget(ship, &(active->testWeapon));
					}
				}
				//active->AttackTarget(enemy, &(active->testWeapon));
			}
			//player->AttackTarget(enemy, &(player->testWeapon));
			for (auto& ship : blueTeam) {
				ship->setActive(false);
				ship->restoreMovement();
			}
			for (auto& ship : redTeam) {
				ship->setTargeted(false);
			}
			active = NULL;
		}

		//Fire Button For Red Team
		else if (turn == 1 && SDL_PointInRect(&point, &moveButton->getBox())) {
			turn = 0;
			if (active != NULL) {
				for (auto& ship : blueTeam) {
					if (ship->getTargeted()) {
						active->AttackTarget(ship, &(active->testWeapon));
					}
				}
				
			}
			//enemy->AttackTarget(player, &(enemy->testWeapon));
			for (auto& ship : redTeam) {
				ship->setActive(false);
				ship->restoreMovement();
			}
			for (auto& ship : blueTeam) {
				ship->setTargeted(false);
			}
			active = NULL;
		}
		/*else {
			if (temp != NULL)
				temp->setActive(false);
			temp = NULL;
		}*/

		break;
	case SDL_MOUSEBUTTONUP:
		if (temp != NULL)
		{
			int distance = temp->getRange(floor(temp->getBox().x) / 32, floor(temp->getBox().y) / 32);
			if (distance <= temp->getMovePoints())
			{
				SDL_Log("In Move Range");
				temp->setLocation(floor(temp->getBox().x) / 32, floor(temp->getBox().y) / 32);
				temp->reduceMovement(distance);
			}
			else
			{
				SDL_Log("Out of Move Range.");
				temp->xpos = temp->getLocationX() * 32;
				temp->ypos = temp->getLocationY() * 32;
			}
			//temp->setActive(false);
			temp = NULL;
		}
		break;
	case SDL_MOUSEMOTION:
		if (temp != NULL && temp->getActive()) {
			if (event.button.x < 960) {
				temp->xpos = event.button.x;
			}
			if (event.button.y < 640) {
				temp->ypos = event.button.y;
			}
			
			//temp->setLocation(floor(temp->getBox().x) / 32, floor(temp->getBox().y) / 32);
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

		case SDLK_r:
			player->setFacingRight();
			break;
		case SDLK_t:
			player->setFacingUp();
			break;
		case SDLK_y:
			player->setFacingLeft();
			break;
		case SDLK_u:
			player->setFacingDown();
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
	for (auto& player_ship : blueTeam) {
		player_ship->Update();
	}
	for (auto& enemy_ship : redTeam) {
		enemy_ship->Update();
	}
	fireButton->Update();
	moveButton->Update();
	
	int deadShipsBlue = 0;
	int deadShipsRed = 0;
	for (auto& ship : blueTeam) {
		if (ship->getHull() <= 0) {
			deadShipsBlue++;
		}
	}
	for (auto& ship : redTeam) {
		if (ship->getHull() <= 0) {
			deadShipsRed++;
		}
	}

	if (deadShipsBlue == blueTeam.size()) {
		endText = "Red Team Wins\n";
		done = true;
	}

	if (deadShipsRed == redTeam.size()) {
		endText = "Blue Team Wins\n";
		done = true;
	}

	if (turn == 0) {
		showText = "Blue Team's Turn";
	}
	if (turn == 1) {
		showText = "Red Team's Turn";
	}

	

	//surf = TTF_RenderText_Solid(font, showText.c_str(), { 255,255,255 });
	//text = SDL_CreateTextureFromSurface(renderer, surf);
	//int textW, textH = 0;
	//SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
	//SDL_Rect dstrect = { 480 - (textW / 2), 672, textW, textH };
	//manager.update();
}  

void Game::render()
{	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	if (done) {
		gameCount++;
		UIFunciton::RenderHPText(555, 200, "assets/Android.ttf", 50, endText, { 255,255,255 });
		if (gameCount == 300) {
			gameCount = 0;
			isRunning = false;
		}
	}
	else {
		map->drawMap();
		for (auto& player_ship : blueTeam) {
			player_ship->Render();
		}
		for (auto& enemy_ship : redTeam) {
			enemy_ship->Render();
		}
		if (turn == 0) {
			fireButton->Render();
		}
		if (turn == 1) {
			moveButton->Render();
		}
		UIFunciton::RenderHPText(480, 672, "assets/Android.ttf", 32, showText, { 255,255,255 });
		UIFunciton::RenderHPText(1034, 32, "assets/Android.ttf", 22, "Ship Info", { 255,255,255 });
		//SDL_RenderCopy(renderer, text, NULL, &dstrect);
	}
	
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	std::cout << "Game cleaned..." << std::endl;
}

bool Game::running()
{
	return isRunning;
}

