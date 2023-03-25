#pragma once

#include "GameEngine.h"

class TextureMenager
{
	public:
		static SDL_Texture* LoadTexture(const char* fileName);
		static void Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);
};