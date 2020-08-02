#include "button.h"
#include "TextureManager.h"

Button::Button(const char* textureSheet, int x, int y, int w, int h)
{
	buttonTexture = TextureManager::loadTexture_BMP(textureSheet);
	isActive = false;
	destBox.x = x;
	destBox.y = y;
	destBox.w = w;
	destBox.h = h;

}

void Button::Update() {

	srcBox.h = 32;
	srcBox.w = 128;
	srcBox.x = 0;
	srcBox.y = 0;

	if (isActive) {
		std::cout << "Button Is Active" << std::endl;
	}
	

}

void Button::Render() {

	SDL_RenderCopy(Game::renderer, buttonTexture, &srcBox, &destBox);

}

void Button::swapActive()
{
	isActive = !isActive;
}

bool Button::getActive()
{
	return isActive;
}

SDL_Rect Button::getBox()
{
	return destBox;
}