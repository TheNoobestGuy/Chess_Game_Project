#pragma once

#include "Figure.h"

class Pawn : public Figure
{
	private:
		Field_ID moves_list[2][2] =
		{
			// White pawn
			{ { 0, -1}, { 0, -2}},

			// Black pawn
			{ { 0,  1}, { 0,  2}}
		};

		Field_ID attacks_list[3][2] =
		{
			// White pawn
			{ {-1, -1}, { 1, -1} },

			// Black pawn
			{ {-1,  1}, { 1,  1} },

			// En passant
			{ {-1,  0}, { 1,  0} }
		};

		Texture pawns_textures[2] =
		{
			{ TextureMenager::LoadTexture("Textures/Figures/white_pawn.png") },
			{ TextureMenager::LoadTexture("Textures/Figures/black_pawn.png") }
		};

	public:
		using Figure::Figure;

		void AvailableMoves(Field* chessboard[8][8]);

		void Render();
};

