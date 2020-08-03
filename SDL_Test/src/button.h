#pragma once
#include "Game.h"

//enum ButtonState {NORMAL=0, HOVER=1, PRESSED=2};

class Button {
private:
	SDL_Rect srcBox, destBox;
	SDL_Texture* buttonTexture;
	
	bool isActive;

public:
	Button(const char* textureSheet, int x, int y, int w, int h, int sh, int sw);

	SDL_Rect getBox();

	void Update();
	void Render();

	void swapActive();

	bool getActive();

	bool isPressed;
};