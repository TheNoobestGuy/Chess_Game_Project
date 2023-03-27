#include "Pawn.h"

Pawn::Pawn(int row_pos, int column_pos, int color, int set)
{
	this->row_pos = row_pos;
	this->column_pos = column_pos;
	this->color = color;
	this->set = set;

	GameEngine::RectangleHandler(&srcRect, &destRect, 64, 64);

	// Available moves list
	if (color == 0)
		available_move = -1;
	else if (color == 1)
		available_move = 1;

	texture = pawns_textures[color][set];
}

Pawn::~Pawn() {}

void Pawn::Update()
{
	// Position
	if (!in_motion)
	{
		if (putted_back)
		{
			// Change position of figure
			chessboard[row_pos][column_pos].figure = false;

			row_pos = std::get<0>(possible_moves[0]);

			chessboard[row_pos][column_pos].figure = true;

			possible_moves.clear();

			// Change player after move
			if (color == 0)
				GameEngine::SetCurrentPlayer(1);
			else if (color == 1)
				GameEngine::SetCurrentPlayer(0);
		}

		destRect.x = column_pos * 64;
		destRect.y = row_pos * 64;
		chessboard[row_pos][column_pos].figure = true;

		picked_up = false;
		putted_back = false;
	}
	else
	{
		picked_up = true;

		// Make figure to follow cursor
		destRect.x = GameEngine::MouseGetX() - 32;
		destRect.y = GameEngine::MouseGetY() - 32;
	}
	 
	// Calculating possible moves
	if (possible_moves.empty() && !in_motion)
	{
		if (!chessboard[row_pos + available_move][column_pos].figure)
		{
			possible_moves.push_back(std::tuple<int, int, SDL_Rect> (row_pos + available_move, column_pos, GameEngine::CreateRectangle(column_pos, row_pos + available_move, 64)));
		}
	}
	else
	{
		if (picked_up)
		{
			for (std::tuple<int, int, SDL_Rect> move : possible_moves)
			{
				if (GameEngine::CollisionDetector(&std::get<2>(move), &destRect))
					putted_back = true;
				else
					putted_back = false;
			}
		}
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

	// Draw available moves
	if (in_motion)
		TextureMenager::Draw(letter_tags[0], srcRect, std::get<2>(possible_moves[0]));

	// Draw figure
	TextureMenager::Draw(texture, srcRect, destRect);
}
