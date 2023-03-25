#pragma once

#include "Figure.h"

class Pawn : protected Figure
{
	public:
		// Inheritance of constructor
		using Figure::Figure;

		void Update();
		void Render();

	private:
		void MovesList();

		SDL_Texture* texture = pawns_textures[color][set];
};

