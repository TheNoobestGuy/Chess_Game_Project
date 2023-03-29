#pragma once

#include "Figure.h"

class Pawn : public Figure
{
	private:
		Field_ID moves_list[2][1] =
		{
			{ { 0, -1} },
			{ { 0,  1} }
		};

		Field_ID attacks_list[2][2] =
		{
			{ {-1, -1}, { 1, -1} },
			{ {-1,  1}, { 1,  1} }
		};

	public:
		using Figure::Figure;

		void AvailableMoves();
};

