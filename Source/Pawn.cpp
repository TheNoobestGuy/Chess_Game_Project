#include "Pawn.h"

#include <iostream>

void Pawn::PossibleMoves()
{

}

void Pawn::Update()
{
	PossibleMoves();

	// Position
	if (!in_motion)
	{
		destRect.x = column_pos * 64;
		destRect.y = row_pos * 64;

		// Appending to chessboard
		chessboard[row_pos][column_pos].figure = 1;
	}
	else
	{
		destRect.x = GameEngine::GetMouseX() - 32;
		destRect.y = GameEngine::GetMouseY() - 32;
	}
}

void Pawn::Render()
{
	// Motion of figure
	if (in_motion)
	{
		// Replace figure field with blank field
		if (chessboard[row_pos][column_pos].texture == 'X')
			TextureMenager::Draw(fields_colors[0], srcRect, destRect);
		else
			TextureMenager::Draw(fields_colors[1], srcRect, destRect);
	}

	TextureMenager::Draw(texture, srcRect, destRect);
}
