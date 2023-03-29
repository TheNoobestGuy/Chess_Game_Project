#include "TextureMenager.h"

SDL_Texture* TextureMenager::LoadTexture(const char* fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(GameEngine::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureMenager::Draw(SDL_Texture* texture, SDL_Rect &srcRect, SDL_Rect &destRect)
{
	SDL_RenderCopy(GameEngine::renderer, texture, &srcRect, &destRect);
}