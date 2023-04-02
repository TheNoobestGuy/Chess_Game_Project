#pragma once

#include "Figure.h"

class Bishop : public Figure
{
	private:
		std::stack<Field_ID> current_moves;

		Field_ID moves_list[4] =
		{
			//             Curve axis
			{ -1, -1}, { 1, -1}, { 1, 1}, { -1, 1}
		};

		Texture bishop_textures[2] =
		{
			{ TextureMenager::LoadTexture("Textures/Figures/white_bishop.png") },
			{ TextureMenager::LoadTexture("Textures/Figures/black_bishop.png") }
		};

	public:
		using Figure::Figure;

		void AvailableMoves(Field* chessboard[8][8]);

		void Render();
};

