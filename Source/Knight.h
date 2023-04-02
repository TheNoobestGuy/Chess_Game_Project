#pragma once

#include "Figure.h"

class Knight : public Figure
{
	private:
		Field_ID moves_list[8] =
		{
			//				 X axis									     Y axis				
			 { -2, -1}, { -2, 1}, { 2, -1}, { 2, 1},    { -1, -2}, { 1, -2}, { 1, 2}, { -1, 2},
		};

		Texture knight_textures[2] =
		{
			{ TextureMenager::LoadTexture("Textures/Figures/white_knight.png") },
			{ TextureMenager::LoadTexture("Textures/Figures/black_knight.png") }
		};

	public:
		using Figure::Figure;

		void AvailableMoves(Field* chessboard[8][8]);

		void Render();
};

