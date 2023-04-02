#include "Rook.h"

void Rook::AvailableMoves(Field* chessboard[8][8])
{
	if (available_moves.empty())
	{
		// Push current position into stack
		current_moves.push({ field_ID.x, field_ID.y });

		// Check possible moves for every available axis
		for (int move = 0; move < 4; move++)
		{
			bool next_axis = false;

			while (!next_axis)
			{
				// Desired move
				int move_x = current_moves.top().x + moves_list[move].x;
				int move_y = current_moves.top().y + moves_list[move].y;

				// Check for collisons with other figures
				if ((move_x >= 0 && move_x < 8) && (move_y >= 0 && move_y < 8))
				{
					if (chessboard[move_y][move_x]->occupied)
					{
						if (chessboard[move_y][move_x]->figure_color != this->color)
						{
							current_moves.push({ move_x, move_y });
							next_axis = true;
						}
						else
						{
							next_axis = true;
						}
					}
					else
					{
						current_moves.push({ move_x, move_y });
					}
				}
				else
					next_axis = true;
			}

			// Push available moves from stack into array
			while (current_moves.size() != 1)
			{
				available_moves.push_back(current_moves.top());
				current_moves.pop();
			}
		}
		current_moves.pop();
	}
}

void Rook::Render()
{
	if (picked_up)
		TextureMenager::Draw(rook_textures[color].texture, rook_textures[color].srcRect, motion_rect);
	else
		TextureMenager::Draw(rook_textures[color].texture, rook_textures[color].srcRect, figure_rect);
}