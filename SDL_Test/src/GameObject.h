#pragma once
#include "Game.h"

class GameObject {
protected:

	
	double angle;

	bool isActive;
	bool isTarget;

	SDL_Texture* objectTexture;
	SDL_Texture* outlineTexture;
	SDL_Rect srcRect, destRect;

public:

	int xpos;
	int ypos;

	GameObject(const char* textureSheet, int x, int y);
	~GameObject();


	void setActive(bool active);
	void setTargeted(bool targeted);
	void unitPosition(int x, int y);

	void swapActive();

	void Update();
	virtual void Render();

	void changeAngle(int angle);

	SDL_Rect getBox();

	bool getActive();
	bool getTargeted();
};
