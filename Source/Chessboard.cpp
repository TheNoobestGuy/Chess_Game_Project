#include "Chessboard.h"

Chessboard::Chessboard(int fields_size)
{
	// Properties
	this->player = 0;
	this->fields_size = fields_size;

	// Update
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
				chessboard[row][col] = new Field { { col, row }, fields_size, color, 0, 0, false };
				color = 0;
			}
			else
			{
				chessboard[row][col] = new Field { { col, row }, fields_size, color, 0, 0, false };
				color = 1;
			}
		}
	}
}

void Chessboard::CreateFigures()
{
	for (int i = 0; i < 8; i++)
	{
		white_player.push_back(new Pawn(i+1, chessboard[6][i]->field_ID, 0, 64));
		black_player.push_back(new Pawn(i+1, chessboard[1][i]->field_ID, 1, 64));
	}

	// ???
	white_player.push_back(new Knight(12, chessboard[7][1]->field_ID, 0, 64));
	white_player.push_back(new Knight(13, chessboard[7][6]->field_ID, 0, 64));

	white_player.push_back(new Rook(14, chessboard[7][0]->field_ID, 0, 64));
	white_player.push_back(new Rook(15, chessboard[7][7]->field_ID, 0, 64));

	white_player.push_back(new Bishop(16, chessboard[7][2]->field_ID, 0, 64));
	white_player.push_back(new Bishop(17, chessboard[7][5]->field_ID, 0, 64));

	white_player.push_back(new Queen(18, chessboard[7][3]->field_ID, 0, 64));

	white_player.push_back(new King(20, chessboard[7][4]->field_ID, 0, 64));
	 

	// ???
	black_player.push_back(new Knight(12, chessboard[0][1]->field_ID, 1, 64));
	black_player.push_back(new Knight(13, chessboard[0][6]->field_ID, 1, 64));

	black_player.push_back(new Rook(14, chessboard[0][0]->field_ID, 1, 64));
	black_player.push_back(new Rook(15, chessboard[0][7]->field_ID, 1, 64));

	black_player.push_back(new Bishop(16, chessboard[0][2]->field_ID, 1, 64));
	black_player.push_back(new Bishop(17, chessboard[0][5]->field_ID, 1, 64));

	black_player.push_back(new Queen(18, chessboard[0][3]->field_ID, 1, 64));

	black_player.push_back(new King(20, chessboard[0][4]->field_ID, 1, 64));
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

void Chessboard::SwitchTurns()
{
	if (update_board)
	{
		switch (player)
		{
			case 0:
				player = 1;
				break;

			case 1:
				player = 0;
				break;

			default:
				break;
		}
	}
}

void Chessboard::MoveFigure()
{
	if (current_figure != nullptr)
	{
		// Check for collision
		if (current_figure->PickedUp())
		{
			for (int move = 0; move < current_figure->available_moves.size(); move++)
			{
				if (GameEngine::CollisionDetector(current_figure->GetMotionRect(), &chessboard[current_figure->available_moves[move].y][current_figure->available_moves[move].x]->field_rect))
				{
					if (!make_move)
					{
						std::cout << "MOVE HERE" << std::endl;

						move_to.x = current_figure->available_moves[move].x;
						move_to.y = current_figure->available_moves[move].y;
						make_move = true;

						last_collision = &chessboard[current_figure->available_moves[move].y][current_figure->available_moves[move].x]->field_rect;
					}
				}
				else if (last_collision != nullptr)
				{
					if (!GameEngine::CollisionDetector(current_figure->GetMotionRect(), last_collision))
					{
						std::cout << "NO MOVE" << std::endl;

						make_move = false;
						last_collision = nullptr;
					}
				}
			}
		}

		// Send new field ID to figure and check is there any collision with some other figures
		if (make_move && !current_figure->PickedUp())
		{
			// Attack
			if (chessboard[move_to.y][move_to.x]->occupied && chessboard[move_to.y][move_to.x]->figure_color != current_figure->GetColor())
			{
				// Delete figure from attacking field
				if (current_figure->GetColor() == 0)
				{
					for (Figure* figure : black_player)
					{
						if (figure->GetFigureID() == chessboard[move_to.y][move_to.x]->figure_ID)
						{
							figure->Delete();
							break;
						}
					}
				}
				else if (current_figure->GetColor() == 1)
				{
					for (Figure* figure : white_player)
					{
						if (figure->GetFigureID() == chessboard[move_to.y][move_to.x]->figure_ID)
						{
							figure->Delete();
							break;
						}
					}
				}

				// Make move
				current_figure->ChangePosition(move_to);
				update_board = true;
				make_move = false;
			}
			// Make move to free field
			else if (!chessboard[move_to.y][move_to.x]->occupied)
			{
				current_figure->ChangePosition(move_to);
				update_board = true;
				make_move = false;
			}

			current_figure = nullptr;
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

void Chessboard::BoardUpdate()
{
	if (update_board)
	{
		// Update positions of figures on board
		for (int row = 0; row < 8; row++)
		{
			for (int col = 0; col < 8; col++)
			{
				bool appended_figure = false;

				for (Figure* figure : white_player)
				{
					if (row == figure->GetFieldID().y && col == figure->GetFieldID().x)
					{
						chessboard[row][col]->figure_ID = figure->GetFigureID();
						chessboard[row][col]->figure_color = 0;
						chessboard[row][col]->occupied = true;
						appended_figure = true;
						break;
					}
				}

				if (!appended_figure)
				{
					for (Figure* figure : black_player)
					{
						if (row == figure->GetFieldID().y && col == figure->GetFieldID().x)
						{
							chessboard[row][col]->figure_ID = figure->GetFigureID();
							chessboard[row][col]->figure_color = 1;
							chessboard[row][col]->occupied = true;
							appended_figure = true;
							break;
						}
					}
				}

				if (!appended_figure)
				{
					chessboard[row][col]->figure_ID = 0;
					chessboard[row][col]->occupied = false;
					chessboard[row][col]->figure_color = 0;
				}
			}
		}

		// Update possible moves of figures whose turn is now
		if (player == 0)
		{
			for (Figure* figure : white_player)
			{
				figure->available_moves.clear();
				figure->AvailableMoves(chessboard);
			}
		}
		else if (player == 1)
		{
			for (Figure* figure : black_player)
			{
				figure->available_moves.clear();
				figure->AvailableMoves(chessboard);
			}
		}

		update_board = false;
	}
}

void Chessboard::UpdateFigures()
{
	PickedUpFigure();

	if (player == 0)
	{
		for (Figure* figure : white_player)
		{
			figure->PickUp();
		}
	}
	else
	{
		for (Figure* figure : black_player)
		{
			figure->PickUp();
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