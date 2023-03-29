#include "Pawn.h"

void Pawn::AvailableMoves()
{
	if (available_moves.empty() && !picked_up)
	{
		for (int move = 0; move < 1; move++)
		{
			available_moves.push_back({ field_ID.row + moves_list[color][move].row, field_ID.col + moves_list[color][move].col });
		}
	}
}
