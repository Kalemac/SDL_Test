#pragma once
#include "Game.h"

class GameObject {
private:

	int xpos;
	int ypos;
	double angle;

	SDL_Texture* objectTexture;
	SDL_Rect srcRect, destRect;

public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	void Update();
	void Render();


};
