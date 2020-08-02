#include "AttackAnim.h"
#include "TextureManager.h"

AttackAnim::AttackAnim(const char* textureSheet, int start_x, int start_y, int end_x, int end_y)
{
	objectTexture = TextureManager::loadTexture_BMP(textureSheet);
	xpos = start_x;
	ypos = start_y;
	xend = end_x;
	yend = end_y;

	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 16;
	destRect.w = destRect.h = 16;
	destRect.x = xpos;
	destRect.y = ypos;

	xspeed = (xend - xpos) / 60;
	yspeed = (yend - ypos) / 60;


	reachedTarget = false;
}

void AttackAnim::update()
{
	


	xpos += xspeed;
	ypos += yspeed;

	destRect.x = xpos;
	destRect.y = ypos;

	if (ypos == yend && xpos == xend) {
		reachedTarget = true;
	}
}

void AttackAnim::render()
{
	SDL_RenderCopyEx(Game::renderer, objectTexture, &srcRect, &destRect, NULL, NULL, SDL_FLIP_NONE);
}
