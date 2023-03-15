#pragma once

#include "GameEngine.h"

class TextureMenager
{
	public:
		static SDL_Texture* LoadTexture(const char* fileName);
};