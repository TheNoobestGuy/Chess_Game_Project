#include "Chessboard.h"

Chessboard::Chessboard(int fields_size)
{
	this->player = 0;
	this->fields_size = fields_size;

	this->make_move = false;
	this->move_to = { 0, 0 };
	this->moved_figure = false;

	this->current_figure = nullptr;
	for (int i = 0; i < 8; i++)
	{
		this->white_player[i] = nullptr;
		this->black_player[i] = nullptr;
	}
}

Chessboard::~Chessboard() {}

void Chessboard::CreateBoard()
{
	bool color = false;

	for (int row = 0; row < 8; row++)
	{
		if (row % 2 == 0)
			color = false;
		else
			color = true;

		for (int col = 0; col < 8; col++)
		{
			if (color)
			{
				chessboard[row][col] = { { row, col }, fields_size, color, nullptr };
				color = false;
			}
			else
			{
				chessboard[row][col] = { { row, col }, fields_size, color, nullptr };
				color = true;
			}
		}
	}
}

void Chessboard::CreateFigures()
{
	for (int i = 0; i < 8; i++)
	{
		current_figure = new Pawn(chessboard[i][1].field_ID, 1, 64);
		black_player[i] = current_figure;

		current_figure = new Pawn(chessboard[i][6].field_ID, 0, 64);
		white_player[i] = current_figure;
	}

	current_figure = nullptr;
}

void Chessboard::DrawBoard()
{
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (chessboard[row][col].color)
				TextureMenager::Draw(fields_colors[1].texture, fields_colors[1].srcRect, chessboard[row][col].field_rect);
			else
				TextureMenager::Draw(fields_colors[0].texture, fields_colors[0].srcRect, chessboard[row][col].field_rect);
		}
	}
}

void Chessboard::DrawFigures()
{
	for (int i = 0; i < 8; i++)
	{
		black_player[i]->Render();
		white_player[i]->Render();
	}
}

void Chessboard::SwitchTurns()
{
	if (moved_figure)
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

		moved_figure = false;
	}
}

void Chessboard::BoardTracer()
{
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			for (int i = 0; i < 8; i++)
			{
				if (chessboard[row][col].field_ID.row == white_player[i]->GetFieldID().row && chessboard[row][col].field_ID.col == white_player[i]->GetFieldID().col)
				{
					chessboard[row][col].figure = white_player[i];
					break;
				}
				else if (chessboard[row][col].field_ID.row == black_player[i]->GetFieldID().row && chessboard[row][col].field_ID.col == black_player[i]->GetFieldID().col)
				{
					chessboard[row][col].figure = black_player[i];
					break;
				}
				else
					chessboard[row][col].figure = nullptr;
			}
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
				if (GameEngine::CollisionDetector(current_figure->GetMotionRect(), &chessboard[current_figure->available_moves[move].row][current_figure->available_moves[move].col].field_rect))
				{
					if (!make_move)
					{
						move_to = current_figure->available_moves[move];
						make_move = true;
					}
				}
				else
				{
					if (make_move)
					{
						make_move = false;
					}
				}
			}
		}

		// Send new field ID to figure and check is there any collision with some other figures
		if (make_move && !current_figure->PickedUp())
		{
			// Attack
			if (chessboard[move_to.row][move_to.col].figure != nullptr && chessboard[move_to.row][move_to.col].figure->GetColor() != current_figure->GetColor())
			{
				chessboard[move_to.row][move_to.col].figure->Delete();

				current_figure->ChangePosition(move_to);
				current_figure->available_moves.clear();

				make_move = false;
				moved_figure = true;
			}
			// Move
			else if (chessboard[move_to.row][move_to.col].figure == nullptr)
			{
				current_figure->ChangePosition(move_to);
				current_figure->available_moves.clear();

				make_move = false;
				moved_figure = true;
			}

			current_figure = nullptr;
		}
	}
}

void Chessboard::PickedUpFigure()
{
	for (int i = 0; i < 8; i++)
	{
		if (white_player[i]->PickedUp())
		{
			current_figure = white_player[i];
			break;
		}
		else if (black_player[i]->PickedUp())
		{
			current_figure = black_player[i];
			break;
		}
		else
			current_figure = nullptr;
	}
}

void Chessboard::UpdateFigures()
{
	PickedUpFigure();

	for (int i = 0; i < 8; i++)
	{
		if (player == 0)
			white_player[i]->Update();

		else if (player == 1)
			black_player[i]->Update();
	}

	MoveFigure();
	SwitchTurns();
}

void Chessboard::RenderFigures()
{
	SDL_RenderClear(GameEngine::renderer);

	DrawBoard();
	DrawFigures();

	if (current_figure != nullptr)
		current_figure->Render();

	SDL_RenderPresent(GameEngine::renderer);
}