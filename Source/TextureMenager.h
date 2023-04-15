#pragma once

#include "GameEngine.h"

struct Text
{
	const char* text;
	SDL_Color color;
	SDL_Rect rect;
};

class TextureMenager
{
	public:
		static SDL_Texture* LoadTexture(const char* fileName);
		static void Draw(SDL_Texture* texture, SDL_Rect &srcRect, SDL_Rect &destRect);
		static void DrawText(Text text);
};