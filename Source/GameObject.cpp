#include "GameObject.h"
#include "TextureMenager.h"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureMenager::LoadTexture(texturesheet);
	
	xpos = x;
	ypos = y;
}

GameObject::~GameObject() {}

void GameObject::Update()
{
	xpos++;
	ypos++;

	// Source size of image
	srcRect.w = 462;
	srcRect.h = 595;

	srcRect.x = 0;
	srcRect.y = 0;

	// Desired size of image
	destRect.w = 64;
	destRect.h = 64;

	destRect.x = xpos;
	destRect.y = ypos;


}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
