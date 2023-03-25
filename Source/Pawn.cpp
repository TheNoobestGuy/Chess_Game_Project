#include "Pawn.h"

#include <iostream>

void Pawn::Update()
{
	// Source size of image
	srcRect.w = 462;
	srcRect.h = 595;

	srcRect.x = srcRect.y = 0;

	// Desired size of image
	destRect.w = destRect.h = 64;

	destRect.x = column_pos * 64;
	destRect.y = row_pos * 64;

	// Appending to chessboard
	chessboard[row_pos][column_pos].figure = 1;
}

void Pawn::Render()
{
	TextureMenager::Draw(texture, srcRect, destRect);
}

void Pawn::MovesList()
{

}
