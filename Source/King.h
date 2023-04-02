#pragma once

#include "Figure.h"

class King : public Figure
{
	private:
		std::stack<Field_ID> current_moves;

		Field_ID moves_list[8] =
		{
			//         Straight axis										  Curve axis
			 { 0, -1}, { 0, 1}, { -1, 0}, { 1, 0},				{ -1, -1}, { 1, -1}, { 1, 1}, { -1, 1}
		};

		Texture king_textures[2] =
		{
			{ TextureMenager::LoadTexture("Textures/Figures/white_king.png") },
			{ TextureMenager::LoadTexture("Textures/Figures/black_king.png") }
		};

	public:
		using Figure::Figure;

		void AvailableMoves(Field* chessboard[8][8]);

		void Render();
};

