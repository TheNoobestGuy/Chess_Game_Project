#include "Pawn.h"

void Pawn::AvailableMoves(Field* chessboard[8][8])
{
	if (available_moves.empty())
	{
		// Desired move
		int move_x = field_ID.x + moves_list[color][0].x;
		int move_y = field_ID.y + moves_list[color][0].y;

		// Check for collisons with other figures
		if ((move_x >= 0 && move_x < 8) && (move_y >= 0 && move_y < 8))
		{
			if (!chessboard[move_y][move_x]->occupied)
			{
				available_moves.push_back({ move_x, move_y });

				// Move two fields at once if first move in game
				if (first_move)
				{
					move_x = field_ID.x + moves_list[color][1].x;
					move_y = field_ID.y + moves_list[color][1].y;

					if (!chessboard[move_y][move_x]->occupied)
					{
						available_moves.push_back({ move_x, move_y });
					}
				}
			}
		}

		// Attack feature
		for (int attack = 0; attack < 2; attack++)
		{
			int attack_x = field_ID.x + attacks_list[color][attack].x;
			int attack_y = field_ID.y + attacks_list[color][attack].y;

			if ((attack_x >= 0 && attack_x < 8) && (attack_y >= 0 && attack_y < 8))
			{
				if (chessboard[attack_y][attack_x]->occupied && chessboard[attack_y][attack_x]->figure_color != this->color)
				{
					available_moves.push_back({ attack_x, attack_y });
				}
			}
		}

		// En passant
		for (int en_passant = 0; en_passant < 2; en_passant++)
		{
			int en_passant_x = field_ID.x + attacks_list[2][en_passant].x;
			int en_passant_y = field_ID.y + attacks_list[2][en_passant].y;

			if ((en_passant_x >= 0 && en_passant_x < 8) && (en_passant_y >= 0 && en_passant_y < 8))
			{
				if (chessboard[en_passant_y][en_passant_x]->occupied && chessboard[en_passant_y][en_passant_x]->figure_color != this->color)
				{
					if (chessboard[en_passant_y][en_passant_x]->en_passant)
					{

						// ??????????????????????????????????????????????????????????????????
						en_passant_x = field_ID.x + attacks_list[color][en_passant].x;
						en_passant_y = field_ID.y + attacks_list[color][en_passant].y;

						available_moves.push_back({ en_passant_x, en_passant_y });
					}
				}
			}
		}

		chessboard[field_ID.y][field_ID.x]->en_passant = false;
	}
}

void Pawn::Render()
{
	if (picked_up)
		TextureMenager::Draw(pawns_textures[color].texture, pawns_textures[color].srcRect, motion_rect);
	else
		TextureMenager::Draw(pawns_textures[color].texture, pawns_textures[color].srcRect, figure_rect);
}

