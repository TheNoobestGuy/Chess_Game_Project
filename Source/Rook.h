#pragma once

#include "Figure.h"

class Rook : public Figure
{
	private:
		std::stack<Field_ID> current_moves;

		Field_ID moves_list[4] =
		{
			//         Straight axis
			 { 0, -1}, { 0, 1}, { -1, 0}, { 1, 0}
		};

		Texture rook_textures[2] =
		{
			{ TextureMenager::LoadTexture("Textures/Figures/white_rook.png") },
			{ TextureMenager::LoadTexture("Textures/Figures/black_rook.png") }
		};

	public:
		using Figure::Figure;

		void AvailableMoves(Field* chessboard[8][8]);

		void Render();
};

