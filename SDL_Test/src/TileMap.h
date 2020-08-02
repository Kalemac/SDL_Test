#pragma once

#include "Game.h"

class TileMap {
private:

	SDL_Rect src, dest;
	SDL_Texture* space;
	SDL_Texture* rock;
	SDL_Texture* other;

	int map[20][30];

public:

	TileMap();
	~TileMap();

	void loadMap(int arr[20][30]);
	void drawMap();
};
