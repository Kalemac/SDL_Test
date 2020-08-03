#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
class Game
{
private:

	bool isRunning;
	SDL_Window *window;

public:

	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void eventHandler();
	void update();
	void render();
	void clean();

	//void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);

	bool running();

	static SDL_Renderer * renderer;
	static SDL_Event event;

	TTF_Font* font = TTF_OpenFont("assets/Android.ttf", 12);

};

