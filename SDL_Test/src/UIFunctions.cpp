#include "UIFunctions.h"


void UIFunciton::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor) {
	Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
	SDL_Color old;
	SDL_GetRenderDrawColor(Game::renderer, &old.r, &old.g, &old.g, &old.a);
	SDL_Rect bgrect = { x, y, w, h };
	SDL_SetRenderDrawColor(Game::renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
	SDL_RenderFillRect(Game::renderer, &bgrect);
	SDL_SetRenderDrawColor(Game::renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
	int pw = (int)((float)w * Percent);
	int px = x + (w - pw);
	SDL_Rect fgrect = { px, y, pw, h };
	SDL_RenderFillRect(Game::renderer, &fgrect);
	SDL_SetRenderDrawColor(Game::renderer, old.r, old.g, old.b, old.a);
}

void UIFunciton::RenderHPText(int x, int y, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color)
{
	SDL_Rect text_rect;
	
	TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
	if (!font) {
		SDL_Log("failed to load font\n");
	}

	auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
	if (!text_surface) {
		SDL_Log("failed to create text surface\n");
	}
	auto text_texture = SDL_CreateTextureFromSurface(Game::renderer, text_surface);
	if (!text_texture) {
		SDL_Log("failed to create text texture");
	}

	SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);
	text_rect.x = x - (text_rect.w / 2);
	text_rect.y = y;
	
	SDL_FreeSurface(text_surface);
	TTF_CloseFont(font);
	SDL_RenderCopy(Game::renderer, text_texture, nullptr, &text_rect);
	SDL_DestroyTexture(text_texture);
}
