#pragma once

#include "Figure.h"

class Pawn : public Figure
{
	public:
		// Inheritance of constructor
		using Figure::Figure;

		// Inheritance of functions
		using Figure::MouseColliding;
		using Figure::InMotionSetter;
		using Figure::RectGetter;

		void Update();
		void Render();

	private:
		void PossibleMoves();

		SDL_Texture* texture = pawns_textures[color][set];
};

