#include "King.h"

void King::AvailableMoves(Field* chessboard[8][8])
{
	if (available_moves.empty())
	{
		// Check possible moves for every available axis
		for (int move = 0; move < 8; move++)
		{
			// Desired move
			int move_x = field_ID.x + moves_list[move].x;
			int move_y = field_ID.y + moves_list[move].y;

			// Check for collisons with other figures
			if ((move_x >= 0 && move_x < 8) && (move_y >= 0 && move_y < 8))
			{
				if (chessboard[move_y][move_x]->occupied)
				{
					if (chessboard[move_y][move_x]->figure_color != this->color)
					{
						available_moves.push_back({ move_x, move_y });
					}
				}
				else
				{
					available_moves.push_back({ move_x, move_y });
				}
			}
		}
	}
}

void King::Render()
{
	if (picked_up)
		TextureMenager::Draw(king_textures[color].texture, king_textures[color].srcRect, motion_rect);
	else
		TextureMenager::Draw(king_textures[color].texture, king_textures[color].srcRect, figure_rect);
}