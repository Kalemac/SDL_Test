#pragma once
#include "Game.h"

class UIFunciton {
public:
	static void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	static void RenderHPText(int x, int y, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);
};