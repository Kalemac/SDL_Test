#pragma once
#include "Game.h"

class AttackAnim {
private:

	SDL_Texture* objectTexture;
	SDL_Rect srcRect, destRect;
	int xpos, ypos, xend, yend;
	int xspeed, yspeed;
	bool reachedTarget;

public:

	AttackAnim(const char* textureSheet, int start_x, int start_y, int end_x, int end_y);

	void update();
	void render();

	bool hasReachedTarget() { return reachedTarget; };
};