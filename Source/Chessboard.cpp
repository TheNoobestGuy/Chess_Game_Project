#include "Chessboard.h"

Chessboard::Chessboard(int fields_size)
{
	// Properties
	this->player = 1;
	this->fields_size = fields_size;

	// Update
	this->checkmate = false;
	this->figure_picked_up = false;
	this->make_move = false;
	this->move_to = { 0, 0 };
	this->update_board = true;

	// Chessboard
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			chessboard[row][col] = nullptr;
		}
	}

	// Figures
	this->white_king = nullptr;
	this->black_king = nullptr;
	this->current_figure = nullptr;
	this->last_collision = nullptr;

	for (Figure* figure : white_player)
	{
		figure = nullptr;
	}
	for (Figure* figure : black_player)
	{
		figure = nullptr;
	}
}

Chessboard::~Chessboard() {}

void Chessboard::CreateBoard()
{
	int color = 0;

	for (int row = 0; row < 8; row++)
	{
		if (row % 2 == 0)
			color = 0;
		else
			color = 1;

		for (int col = 0; col < 8; col++)
		{
			if (color == 1)
			{
				chessboard[row][col] = new Field{ { col, row }, fields_size, color};
				color = 0;
			}
			else
			{
				chessboard[row][col] = new Field { { col, row }, fields_size, color};
				color = 1;
			}
		}
	}
}

void Chessboard::CreateFigures()
{
	int ID = 1;

	// Pawns
	std::string name = "Pawn";
	for (int i = 0; i < 8; i++, ID++)
	{
		white_player.push_back(new Pawn(name, ID, chessboard[6][i]->field_ID, 0, 64));
		black_player.push_back(new Pawn(name, ID, chessboard[1][i]->field_ID, 1, 64));
	}

	// Knights
	name = "Knight";
	for (int i = 1; i < 8; i+=5, ID++)
	{
		white_player.push_back(new Knight(name, ID, chessboard[7][i]->field_ID, 0, 64));
		black_player.push_back(new Knight(name, ID, chessboard[0][i]->field_ID, 1, 64));
	}

	// Bishops
	name = "Bishop";
	for (int i = 2; i < 8; i+=3, ID++)
	{
		white_player.push_back(new Bishop(name, ID, chessboard[7][i]->field_ID, 0, 64));
		black_player.push_back(new Bishop(name, ID, chessboard[0][i]->field_ID, 1, 64));
	}

	// Rooks
	name = "Rook";
	for (int i = 0; i < 8; i+=7, ID++)
	{
		white_player.push_back(new Rook(name, ID, chessboard[7][i]->field_ID, 0, 64));
		black_player.push_back(new Rook(name, ID, chessboard[0][i]->field_ID, 1, 64));
	}

	// Queens
	name = "Queen";
	white_player.push_back(new Queen(name, ID, chessboard[7][3]->field_ID, 0, 64));
	black_player.push_back(new Queen(name, ID, chessboard[0][3]->field_ID, 1, 64));

	// Kings
	name = "King";
	ID++;
	white_player.push_back(new King(name, ID, chessboard[7][4]->field_ID, 0, 64));
	white_king = white_player.back();

	black_player.push_back(new King(name, ID, chessboard[0][4]->field_ID, 1, 64));
	black_king = black_player.back();

	// Append moves
	for (Figure* figure : white_player)
	{
		figure->PossibleMoves();
	}
	for (Figure* figure : black_player)
	{
		figure->PossibleMoves();
	}
}

void Chessboard::DrawBoard()
{
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (chessboard[row][col]->color)
				TextureMenager::Draw(fields_colors[1].texture, fields_colors[1].srcRect, chessboard[row][col]->field_rect);
			else
				TextureMenager::Draw(fields_colors[0].texture, fields_colors[0].srcRect, chessboard[row][col]->field_rect);
		}
	}
}

void Chessboard::DrawFigures()
{
	for (Figure* figure : white_player)
	{
		figure->Render();
	}

	for (Figure* figure : black_player)
	{
		figure->Render();
	}
}

void Chessboard::BoardUpdate()
{
	if (update_board)
	{
		// Remove from board conquered figures
		while (!removed_figures.empty())
		{
			if (removed_figures.top()->GetPlayer() == 1)
			{
				for (int figure = 0; figure < white_player.size(); figure++)
				{
					if (white_player[figure]->GetID() == removed_figures.top()->GetID())
					{
						white_player[figure] = nullptr;
						white_player.erase(white_player.begin() + figure);
						removed_figures.pop();
						break;
					}
				}
			}
			else if (removed_figures.top()->GetPlayer() == 2)
			{
				for (int figure = 0; figure < black_player.size(); figure++)
				{
					if (black_player[figure]->GetID() == removed_figures.top()->GetID())
					{
						black_player[figure] = nullptr;
						black_player.erase(black_player.begin() + figure);
						removed_figures.pop();
						break;
					}
				}
			}
		}

		// Attach positions of figures to board
		for (int row = 0; row < 8; row++)
		{
			for (int col = 0; col < 8; col++)
			{
				bool appended_figure = false;

				for (Figure* figure : white_player)
				{
					if (row == figure->GetField().y && col == figure->GetField().x)
					{
						chessboard[row][col]->figure = figure;
						chessboard[row][col]->figure->Release();
						appended_figure = true;
						break;
					}
				}

				if (!appended_figure)
				{
					for (Figure* figure : black_player)
					{
						if (row == figure->GetField().y && col == figure->GetField().x)
						{
							chessboard[row][col]->figure = figure;
							chessboard[row][col]->figure->Release();
							appended_figure = true;
							break;
						}
					}
				}

				if (!appended_figure)
				{
					chessboard[row][col]->figure = nullptr;
				}

				chessboard[row][col]->field_under_attack[0] = false;
				chessboard[row][col]->field_under_attack[1] = false;
				chessboard[row][col]->en_passant = false;
			}
		}

		// Calculate available moves for figures
		CalculateFigureMoves(white_player);
		CalculateFigureMoves(black_player);

		// Mark fields under attack
		MarkFieldsUnderAttack(white_player);
		MarkFieldsUnderAttack(black_player);

		// Check for entangling
		CheckForEntangling(white_player, black_king);
		CheckForEntangling(black_player, white_king);

		ApplyEntangledMoves(white_player);
		ApplyEntangledMoves(black_player);

		// Kings mechanics
		KingMechanic(white_player, black_player, white_king);
		KingMechanic(black_player, white_player, black_king);

		// End game conditions check
		EndGameConditions(white_player, white_king);
		EndGameConditions(black_player, black_king);

		update_board = false;
	}
}

void Chessboard::SwitchTurns()
{
	if (update_board)
	{
		switch (player)
		{
		case 1:
			player = 2;
			break;

		case 2:
			player = 1;
			break;

		default:
			break;
		}
	}
}

void Chessboard::UpdateFigures()
{
	PickedUpFigure();

	if (player == 1)
	{
		for (Figure* figure : white_player)
		{
			figure->PickUp(figure_picked_up);
		}
	}
	else if (player == 2)
	{
		for (Figure* figure : black_player)
		{
			figure->PickUp(figure_picked_up);
		}
	}

	MoveFigure();
}

void Chessboard::RenderFigures()
{
	SDL_RenderClear(GameEngine::renderer);

	DrawBoard();
	DrawFigures();

	DrawMarksForMovesWhenPicked(white_player);
	DrawMarksForMovesWhenPicked(black_player);

	// Render the picked up figure in front
	if (current_figure != nullptr)
		current_figure->Render();

	SDL_RenderPresent(GameEngine::renderer);
} 

void Chessboard::KingMechanic(std::vector<Figure*> player_figures, std::vector<Figure*> opposite_player_figures, Figure* king)
{
	// Deduce opposite player
	int opposite_player = 1;

	if (king->GetPlayer() == 2)
		opposite_player = 0;

	// Remove unavailable moves from king pool of moves
	std::vector<Field_ID> buffor;

	for (Field_ID move : king->available_moves)
	{
		if (!chessboard[move.y][move.x]->field_under_attack[opposite_player])
		{
			buffor.push_back(move);
		}
	}
	king->available_moves = buffor;

	// Check is there a checkmate and calculate possible moves to save king if there are any
	if (chessboard[king->GetField().y][king->GetField().x]->field_under_attack[opposite_player])
	{
		checkmate = true;

		// Find common attacked fields to defend
		std::vector<Field_ID> common_fields;

		for (Figure* opposite_figure_1 : opposite_player_figures)
		{
			for (Field_ID attack_1 : opposite_figure_1->way_to_opposite_king)
			{
				for (Figure* opposite_figure_2 : opposite_player_figures)
				{
					if (opposite_figure_1->GetID() != opposite_figure_2->GetID())
					{
						for (Field_ID attack_2 : opposite_figure_2->way_to_opposite_king)
						{
							if (attack_1 == attack_2)
							{
								common_fields.push_back(attack_1);
							}
						}
					}
				}
			}

			if (common_fields.empty())
			{
				common_fields = opposite_figure_1->way_to_opposite_king;
			}
		}

		// Find if there is possible defence by move of figures
		for (Figure* figure : player_figures)
		{
			if (figure->GetName() == "Pawn")
			{
				buffor.clear();

				for (Field_ID defence : figure->available_moves)
				{
					for (Field_ID attack : common_fields)
					{
						if (chessboard[defence.y][defence.x]->figure != nullptr && defence.x == figure->GetField().x)
						{
							continue;
						}
						else
						{
							if (defence == attack)
							{
								buffor.push_back(defence);
							}
						}
					}
				}

				figure->available_moves = buffor;
			}

			else if (figure->GetName() != "King")
			{
				buffor.clear();

				for (Field_ID defence : figure->available_moves)
				{
					for (Field_ID attack : common_fields)
					{
						if (defence == attack)
						{
							buffor.push_back(defence);
						}
					}
				}

				figure->available_moves = buffor;
			}
		}
	}
	else
	{
		checkmate = false;
	}
}

void Chessboard::CheckForEntangling(std::vector<Figure*> player_figures, Figure* opposite_king)
{
	for (Figure* figure : player_figures)
	{
		if (figure->GetName() != "King")
		{
			// Check every possible axis of move and entangle figure that is standing at way of attack on king
			for (int move_axis = 0; move_axis < 8; move_axis++)
			{
				Figure* entangled_figure = nullptr;
				std::vector<Field_ID> way_to_king;
				way_to_king.push_back({ figure->GetField().x, figure->GetField().y });
				int figures_counter = 0;

				for (Field_ID field : figure->available_moves)
				{
					if (field.move_axis == move_axis)
					{
						// Keep counter of encountering figure and skip every axis where there is more than one
						if (chessboard[field.y][field.x]->figure != nullptr)
						{
							if (figures_counter == 0)
							{
								if (chessboard[field.y][field.x]->figure->GetName() == "King")
								{
									break;
								}
								else
								{
									entangled_figure = chessboard[field.y][field.x]->figure;
									figures_counter++;
								}
							}
							else if (figures_counter >= 1)
							{
								// If there is encountered opposite king at the way push possible moves for entangled figure into an array of moves
								if (chessboard[field.y][field.x]->figure->GetName() == "King" && figure->GetPlayer() != chessboard[field.y][field.x]->figure->GetPlayer())
								{
									entangled_figure->MakeEntangled();

									for (Field_ID move : entangled_figure->available_moves)
									{
										for (Field_ID way : way_to_king)
										{
											if (move == way)
											{
												entangled_figure->entangled_moves.push_back(way);
											}
										}
									}
								}
								break;
							}
						}
						else
						{
							way_to_king.push_back(field);
							way_to_king.back().available_move = true;
						}
					}
				}

				entangled_figure = nullptr;
			}
		}
	}
}

void Chessboard::ApplyEntangledMoves(std::vector<Figure*> player_figures)
{
	for (Figure* figure : player_figures)
	{
		if (figure->IsItEntangled())
		{
			figure->available_moves = figure->entangled_moves;
		}
	}
}

void Chessboard::EndGameConditions(std::vector<Figure*> player_figures, Figure* king)
{
	// Check if player has available moves
	bool no_moves = true;

	for (Figure* figure : player_figures)
	{
		if (!figure->available_moves.empty())
		{
			no_moves = false;
			break;
		}
	}

	// Win by checkmate
	if (no_moves && checkmate)
	{
		if (king->GetPlayer() == 1)
		{
			std::cout << "BLACK PLAYER WON" << std::endl;
		}
		else if (king->GetPlayer() == 2)
		{
			std::cout << "WHITE PLAYER WON" << std::endl;
		}
	}
	// Pat
	else if (no_moves)
	{
		std::cout << "REMIS" << std::endl;
	}
}

void Chessboard::MarkFieldsUnderAttack(std::vector<Figure*> player_figures)
{
	for (Figure* figure : player_figures)
	{
		int player_pos = figure->GetPlayer() - 1;

		if (figure->GetName() == "Pawn")
		{
			// Static moves applier for Pawns
			int pos_x_1 = figure->GetField().x - 1;
			int pos_x_2 = figure->GetField().x + 1;
			int pos_y = figure->GetField().y;

			if (player_pos == 0)
			{
				pos_y--;
			}
			else if (player_pos == 1)
			{
				pos_y++;
			}

			if (pos_y >= 0 && pos_y < 8)
			{
				if (pos_x_1 >= 0 && pos_x_1 < 8)
				{
					chessboard[pos_y][pos_x_1]->field_under_attack[player_pos] = true;
				}
				if (pos_x_2 >= 0 && pos_x_2 < 8)
				{
					chessboard[pos_y][pos_x_2]->field_under_attack[player_pos] = true;
				}
			}
		}
		else if (figure->GetName() == "King" || figure->GetName() == "Knight")
		{
			// Every possible moves of those figures are also attacks
			for (Field_ID attack : figure->available_moves)
			{
				chessboard[attack.y][attack.x]->field_under_attack[player_pos] = true;
			}
		}
		else if (figure->GetName() == "Bishop" || figure->GetName() == "Rook" || figure->GetName() == "Queen")
		{
			// Check moves by their axis
			int axis = 0;
			bool figure_encountered = false;

			for (Field_ID attack : figure->available_moves)
			{
				if (attack.move_axis != axis)
				{
					axis = attack.move_axis;
					figure_encountered = false;
				}

				if (figure_encountered)
				{
					continue;
				}

				if (chessboard[attack.y][attack.x]->figure != nullptr)
				{
					if (chessboard[attack.y][attack.x]->figure->GetName() != "King")
					{
						figure_encountered = true;
					}

					chessboard[attack.y][attack.x]->field_under_attack[player_pos] = true;
				}
				else
				{
					chessboard[attack.y][attack.x]->field_under_attack[player_pos] = true;
				}
			}
		}
	}
}

void Chessboard::CalculateFigureMoves(std::vector<Figure*> player_figures)
{
	for (Figure* figure : player_figures)
	{
		// Clear unactual available moves
		figure->available_moves.clear();

		// Calculate possible move for figures
		if (figure->GetName() == "King")
		{
			for (int move = 0; move < figure->moves_list.size(); move++)
			{
				// Desired move
				int move_x = figure->GetField().x + figure->moves_list[move].x;
				int move_y = figure->GetField().y + figure->moves_list[move].y;

				// Check for collisons with other figures
				if ((move_x >= 0 && move_x < 8) && (move_y >= 0 && move_y < 8))
				{
					if (chessboard[move_y][move_x]->figure != nullptr)
					{
						if (chessboard[move_y][move_x]->figure->GetPlayer() != figure->GetPlayer())
						{
							figure->available_moves.push_back({ move_x, move_y });
						}
					}
					else
					{
						figure->available_moves.push_back({ move_x, move_y });
					}
				}
			}
		}

		else if (figure->GetName() == "Queen" || figure->GetName() == "Rook" || figure->GetName() == "Bishop")
		{
			for (int move = 0; move < figure->moves_list.size(); move++)
			{
				bool next_axis = false;
				bool unavailable_moves = false;
				std::vector<Field_ID> way_to_king;
				way_to_king.push_back(figure->GetField());

				// Figure beginning position
				int move_x = figure->GetField().x + figure->moves_list[move].x;
				int move_y = figure->GetField().y + figure->moves_list[move].y;

				while (!next_axis)
				{
					// Sort moves on available and unavailable with keeping track of their axis at this moment for further discernion by a marking system later
					if ((move_x >= 0 && move_x < 8) && (move_y >= 0 && move_y < 8))
					{
						if (chessboard[move_y][move_x]->figure != nullptr)
						{
							if (chessboard[move_y][move_x]->figure->GetPlayer() != figure->GetPlayer())
							{
								if (unavailable_moves)
								{
									figure->available_moves.push_back({ move_x, move_y });
									figure->available_moves.back().move_axis = move;
									figure->available_moves.back().available_move = false;
								}
								else
								{
									figure->available_moves.push_back({ move_x, move_y });
									figure->available_moves.back().move_axis = move;
									figure->available_moves.back().available_move = true;

									// If king is encountered append way that is leading to him to proper array
									if (chessboard[move_y][move_x]->figure->GetName() == "King" && chessboard[move_y][move_x]->figure->GetPlayer() != figure->GetPlayer())
									{
										figure->way_to_opposite_king = way_to_king;
										way_to_king.clear();
									}

									unavailable_moves = true;
								}
							}
							// If friendly figure encountered append its position as last attack in axis
							else if (chessboard[move_y][move_x]->figure->GetPlayer() == figure->GetPlayer())
							{
								chessboard[move_y][move_x]->field_under_attack[figure->GetPlayer()-1] = true;
								next_axis = true;
							}
						}
						else
						{	
							if (unavailable_moves)
							{
								figure->available_moves.push_back({ move_x, move_y });
								figure->available_moves.back().move_axis = move;
								figure->available_moves.back().available_move = false;
							}
							else
							{
								figure->available_moves.push_back({ move_x, move_y });
								figure->available_moves.back().move_axis = move;
								figure->available_moves.back().available_move = true;

								way_to_king.push_back(figure->available_moves.back());
							}
						}
					}
					// If move is out of board go to the next axis
					else
					{
						next_axis = true;
					}

					// Desired move
					move_x += figure->moves_list[move].x;
					move_y += figure->moves_list[move].y;
				}

				way_to_king.clear();
			}

		}

		else if (figure->GetName() == "Knight")
		{
			for (int move = 0; move < figure->moves_list.size(); move++)
			{
				// Desired move
				int move_x = figure->GetField().x + figure->moves_list[move].x;
				int move_y = figure->GetField().y + figure->moves_list[move].y;

				// Check for collisons with other figures
				if ((move_x >= 0 && move_x < 8) && (move_y >= 0 && move_y < 8))
				{
					if (chessboard[move_y][move_x]->figure != nullptr)
					{
						if (chessboard[move_y][move_x]->figure->GetPlayer() != figure->GetPlayer())
						{
							figure->available_moves.push_back({ move_x, move_y });
						}
						else if (chessboard[move_y][move_x]->figure->GetPlayer() == figure->GetPlayer())
						{
							chessboard[move_y][move_x]->field_under_attack[figure->GetPlayer()-1] = true;
						}
					}
					else
					{
						figure->available_moves.push_back({ move_x, move_y });
					}
				}
			}
		}

		else if (figure->GetName() == "Pawn")
		{
			// Desired move
			int move_x = figure->GetField().x + figure->moves_list[0].x;
			int move_y = figure->GetField().y + figure->moves_list[0].y;

			if ((move_x >= 0 && move_x < 8) && (move_y >= 0 && move_y < 8))
			{
				if (chessboard[move_y][move_x]->figure == nullptr)
				{
					figure->available_moves.push_back({ move_x, move_y });

					// First move special
					if (figure->IsItFirstMove())
					{
						move_x = figure->GetField().x + figure->moves_list[1].x;
						move_y = figure->GetField().y + figure->moves_list[1].y;

						if (chessboard[move_y][move_x]->figure == nullptr)
						{
							figure->available_moves.push_back({ move_x, move_y });
							figure->EnPassantVulnerablity();
						}
					}
				}
			}

			// Attack
			for (int attack = 2; attack < 4; attack++)
			{
				int attack_x = figure->GetField().x + figure->moves_list[attack].x;
				int attack_y = figure->GetField().y + figure->moves_list[attack].y;

				if ((attack_x >= 0 && attack_x < 8) && (attack_y >= 0 && attack_y < 8))
				{
					if (chessboard[attack_y][attack_x]->figure != nullptr && chessboard[attack_y][attack_x]->figure->GetPlayer() != figure->GetPlayer())
					{
						figure->available_moves.push_back({ attack_x, attack_y });
					}
					else if (chessboard[attack_y][attack_x]->figure != nullptr && chessboard[attack_y][attack_x]->figure->GetPlayer() == figure->GetPlayer())
					{
						chessboard[attack_y][attack_x]->field_under_attack[figure->GetPlayer() - 1] = true;
					}
				}
			}

			// En passant
			for (int en_passant = 4; en_passant < 6; en_passant++)
			{
				int en_passant_x = figure->GetField().x + figure->moves_list[en_passant].x;
				int en_passant_y = figure->GetField().y + figure->moves_list[en_passant].y;

				if ((en_passant_x >= 0 && en_passant_x < 8) && (en_passant_y >= 0 && en_passant_y < 8))
				{
					if (chessboard[en_passant_y][en_passant_x]->figure != nullptr && chessboard[en_passant_y][en_passant_x]->figure->EnPassant())
					{
						if (chessboard[en_passant_y][en_passant_x]->figure->GetName() == "Pawn" && chessboard[en_passant_y][en_passant_x]->figure->GetPlayer() != figure->GetPlayer())
						{
							en_passant_x = figure->GetField().x + figure->moves_list[en_passant - 2].x;
							en_passant_y = figure->GetField().y + figure->moves_list[en_passant - 2].y;

							if (chessboard[en_passant_y][en_passant_x]->figure == nullptr)
							{
								figure->available_moves.push_back({ en_passant_x, en_passant_y });
								chessboard[en_passant_y][en_passant_x]->en_passant = true;
							}
						}
					}
				}
			}
		}
	}
}

void Chessboard::PickedUpFigure()
{
	current_figure = nullptr;

	for (Figure* figure : white_player)
	{
		if (figure->PickedUp())
		{
			current_figure = figure;
			break;
		}
	}

	for (Figure* figure : black_player)
	{
		if (figure->PickedUp())
		{
			current_figure = figure;
			break;
		}
	}

}

void Chessboard::DrawMarksForMovesWhenPicked(std::vector<Figure*> player_figures)
{
	for (Figure* figure : player_figures)
	{
		if (figure->PickedUp())
		{
			// Mark for place from where figure was taken 
			SDL_Rect static_rect = GameEngine::CreateRectangle(figure->GetField().x, figure->GetField().y, fields_size);
			TextureMenager::Draw(marks[1].texture, marks[1].srcRect, static_rect);

			// Marks for available moves
			for (Field_ID field : figure->available_moves)
			{
				if (field.available_move)
				{
					SDL_Rect possble_moves = GameEngine::CreateRectangle(field.x, field.y, fields_size);
					TextureMenager::Draw(marks[0].texture, marks[0].srcRect, possble_moves);
				}
			}
		}
	}
}

void Chessboard::MoveFigure()
{
	if (current_figure != nullptr)
	{
		// Check for collision with board fields while figure raised up
		if (current_figure->PickedUp())
		{
			for (int move = 0; move < current_figure->available_moves.size(); move++)
			{
				if (current_figure->available_moves[move].available_move)
				{
					if (GameEngine::CollisionDetector(current_figure->GetMotionRect(), &chessboard[current_figure->available_moves[move].y][current_figure->available_moves[move].x]->field_rect))
					{
						if (!make_move)
						{
							move_to.x = current_figure->available_moves[move].x;
							move_to.y = current_figure->available_moves[move].y;
							move_to.attacked_figure = chessboard[current_figure->available_moves[move].y][current_figure->available_moves[move].x]->figure;

							make_move = true;
							last_collision = &chessboard[current_figure->available_moves[move].y][current_figure->available_moves[move].x]->field_rect;
						}
					}
					else if (last_collision != nullptr)
					{
						if (!GameEngine::CollisionDetector(current_figure->GetMotionRect(), last_collision))
						{
							move_to.x = 0;
							move_to.y = 0;
							move_to.attacked_figure = nullptr;

							make_move = false;
							last_collision = nullptr;
						}
					}
				}
			}
		}

		// Send new field ID to figure and check if there is any collision with some other figures
		if (make_move && !current_figure->PickedUp())
		{
			// Attack			
			if (move_to.attacked_figure != nullptr && move_to.attacked_figure->GetPlayer() != current_figure->GetPlayer())
			{
				if (player == 1)
				{
					for (Figure* figure : black_player)
					{
						if (figure->GetID() == move_to.attacked_figure->GetID())
						{
							removed_figures.push(figure);
							break;
						}
					}
				}
				else if (player == 2)
				{
					for (Figure* figure : white_player)
					{
						if (figure->GetID() == move_to.attacked_figure->GetID())
						{
							removed_figures.push(figure);
							break;
						}
					}
				}
			}
			// En passant
			if (current_figure->GetName() == "Pawn")
			{
				if (move_to.attacked_figure == nullptr && chessboard[move_to.y][move_to.x]->en_passant == true)
				{
					if (player == 1)
					{
						removed_figures.push(chessboard[move_to.y + 1][move_to.x]->figure);
					}
					else if (player == 2)
					{
						removed_figures.push(chessboard[move_to.y - 1][move_to.x]->figure);
					}
				}
			}

			// Make move
			current_figure->ChangePosition( { move_to.x, move_to.y } );
			update_board = true;
			make_move = false;
			current_figure = nullptr;
		}
	}
}