#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
	objectTexture = TextureManager::loadTexture_BMP(textureSheet);
	xpos = x;
	ypos = y;
	isActive = false;
	isTarget = false;
	angle = 90;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{	
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos - (xpos % 64) + 1;
	destRect.y = ypos - (ypos % 64) + 1;
	destRect.w = 62;
	destRect.h = 62;

	//std::pair<int, int> posPair = GridPos::getGridPos(destRect.x, destRect.y);
	//std::cout << "Grid X: " << floor(destRect.x / 32) << " Grid Y: " << floor(destRect.y / 32) << std::endl;
}


void GameObject::setActive(bool active) {
	isActive = active;
	//std::cout << "Changed value to: " << isActive << std::endl;
}

void GameObject::setTargeted(bool targeted)
{
	isTarget = targeted;
}

void GameObject::unitPosition(int x, int y) {
	xpos = x;
	ypos = y;
}

void GameObject::swapActive()
{
	
	isActive = !isActive;
	//std::cout << "Active is swapped to: " << isActive << std::endl;
}

void GameObject::Render()
{
	SDL_RenderCopyEx(Game::renderer, objectTexture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
}

SDL_Rect GameObject::getBox()
{
	return destRect;
}

void GameObject::changeAngle(int ang) {
	angle = ang;
}

bool GameObject::getActive() {
	//std::cout << "Active: " << isActive << std::endl;
	return isActive;
}

bool GameObject::getTargeted() {
	return isTarget;
}