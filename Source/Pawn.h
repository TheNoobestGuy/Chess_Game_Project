#pragma once

#include "Figure.h"

class Pawn : public Figure
{
	public:
		Pawn(int row_pos, int column_pos, int color, int set);
		~Pawn();

		// Inheritance of functions
		using Figure::InMotionSetter;
		using Figure::RectGetter;

		void Update();
		void Render();

	private:
		int available_move;

		SDL_Texture* texture;
};

