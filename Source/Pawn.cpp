#include "Pawn.h"

#include <iostream>

void Pawn::PossibleMoves()
{
	// Possible move
	SDL_Rect move_variant_src;
	SDL_Rect move_variant_dest;

	// Source size and position of image
	move_variant_src.w = 64;
	move_variant_src.h = 64;
	move_variant_src.x = move_variant_src.y = 0;

	// Desired size of image
	move_variant_dest.w = move_variant_dest.h = 64;
	move_variant_dest.x = column_pos * 64;
	move_variant_dest.y = (row_pos - 1) * 64;

	possible_moves.push_back(std::tuple<SDL_Rect, SDL_Rect> (move_variant_src, move_variant_dest));
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

		//  Highlight possible moves while picked up
		for (std::tuple<SDL_Rect, SDL_Rect> field : possible_moves)
		{
			TextureMenager::Draw(numeric_tags[0], std::get<0>(field), std::get<1>(field));
		}
	}

	TextureMenager::Draw(texture, srcRect, destRect);
}
