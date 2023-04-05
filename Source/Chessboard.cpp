#include "Chessboard.h"

Chessboard::Chessboard(int fields_size)
{
	// Properties
	this->player = 1;
	this->fields_size = fields_size;

	// Update
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
	black_player.push_back(new King(name, ID, chessboard[0][4]->field_ID, 1, 64));

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
			removed_figures.top()->Delete();
			removed_figures.pop();
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

		// Calculate available moves of figures
		CalculateFigureMoves(white_player);
		CalculateFigureMoves(black_player);

		// Mark fields under attack
		MarkFieldsUnderAttack(white_player, 1);
		MarkFieldsUnderAttack(black_player, 0);

		// Kings moves calculating
		KingMechanic(white_player);
		KingMechanic(black_player);

		// TEST ATTACKED FIELDS
		std::cout << std::endl;
		std::cout << "BLACK ATTACKS" << std::endl;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				std::cout << chessboard[i][j]->field_under_attack[0];
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;
		std::cout << "WHITE ATTACKS" << std::endl;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				std::cout << chessboard[i][j]->field_under_attack[1];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

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

	// Render the picked up figure in front
	if (current_figure != nullptr)
		current_figure->Render();

	SDL_RenderPresent(GameEngine::renderer);
} 

void Chessboard::KingMechanic(std::vector<Figure*> player_figures)
{
	for (Figure* figure : player_figures)
	{
		if (figure->GetName() == "King")
		{
			figure->available_moves.clear();

			for (int move = 0; move < figure->moves_list.size(); move++)
			{
				// Desired move
				int move_x = figure->GetField().x + figure->moves_list[move].x;
				int move_y = figure->GetField().y + figure->moves_list[move].y;

				// Check for collisons with other figures
				if ((move_x >= 0 && move_x < 8) && (move_y >= 0 && move_y < 8))
				{
					if (!chessboard[move_y][move_x]->field_under_attack[figure->GetPlayer()-1])
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
		}
	}
}

void Chessboard::MarkFieldsUnderAttack(std::vector<Figure*> player_figures, int array_pos)
{
	for (Figure* figure : player_figures)
	{
		if (figure->GetName() == "Pawn")
		{
			int pos_x_1 = figure->GetField().x - 1;
			int pos_x_2 = figure->GetField().x + 1;
			int pos_y = figure->GetField().y;

			if (array_pos == 1)
			{
				pos_y--;

				if (pos_x_1 >= 0 && pos_x_1 < 8)
				{
					chessboard[pos_y][pos_x_1]->field_under_attack[array_pos] = true;
				}
				if (pos_x_2 >= 0 && pos_x_1 < 8)
				{
					chessboard[pos_y][pos_x_2]->field_under_attack[array_pos] = true;
				}
			}
			else if (array_pos == 0)
			{
				pos_y++;

				if (pos_x_1 >= 0 && pos_x_1 < 8)
				{
					chessboard[pos_y][pos_x_1]->field_under_attack[array_pos] = true;
				}
				if (pos_x_2 >= 0 && pos_x_1 < 8)
				{
					chessboard[pos_y][pos_x_2]->field_under_attack[array_pos] = true;
				}
			}
		}
		else
		{
			for (Field_ID attack : figure->available_moves)
			{
				chessboard[attack.y][attack.x]->field_under_attack[array_pos] = true;
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

		// Stack for every axis of move
		std::stack<Field_ID> current_moves;
		current_moves.push({ figure->GetField().x, figure->GetField().y });

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

				while (!next_axis)
				{
					// Desired move
					int move_x = current_moves.top().x + figure->moves_list[move].x;
					int move_y = current_moves.top().y + figure->moves_list[move].y;

					// Check for collisons with other figures
					if ((move_x >= 0 && move_x < 8) && (move_y >= 0 && move_y < 8))
					{
						if (chessboard[move_y][move_x]->figure != nullptr)
						{
							if (chessboard[move_y][move_x]->figure->GetPlayer() != figure->GetPlayer())
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

				// Push available moves from stack into figure array
				while (current_moves.size() != 1)
				{
					figure->available_moves.push_back(current_moves.top());
					current_moves.pop();
				}
			}
			current_moves.pop();
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

						figure->available_moves.push_back({ move_x, move_y });
						figure->EnPassantVulnerablity();
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
	if (true)
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
				if (GameEngine::CollisionDetector(current_figure->GetMotionRect(), &chessboard[current_figure->available_moves[move].y][current_figure->available_moves[move].x]->field_rect))
				{
					if (!make_move)
					{
						std::cout << "MOVE" << std::endl;

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
						std::cout << "NO MOVE" << std::endl;

						move_to.x = 0;
						move_to.y = 0;
						move_to.attacked_figure = nullptr;

						make_move = false;
						last_collision = nullptr;
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