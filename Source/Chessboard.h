#pragma once

#include "GameEngine.h"

// Figures
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

class Chessboard
{
	private:
		// Properties
		int player;
		int fields_size;

		// Update
		bool make_move;
		Field_ID move_to;
		bool update_board;

		// Chessboard
		Field* chessboard[8][8];

		// Figures
		Figure* current_figure;
		SDL_Rect* last_collision;
		std::vector<Figure*> white_player;
		std::vector<Figure*> black_player;

	public:
		Chessboard(int fields_size);
		~Chessboard();

		// Create objects
		void CreateBoard();
		void CreateFigures();

		// Board features
		void DrawBoard();
		void DrawFigures();
		void SwitchTurns();
		void BoardUpdate();
		void UpdateFigures();
		void RenderFigures();

		// Figures features
		void MoveFigure();
		void PickedUpFigure();


// ****************** TEST TEXTURES ******************
	private:

		bool test = true;

		Texture fields_colors[2] =
		{
			{ TextureMenager::LoadTexture("Textures/Chessboard/whiteSqr.png") },
			{ TextureMenager::LoadTexture("Textures/Chessboard/blackSqr.png") }
		};

		SDL_Texture* numeric_tags[8] =
		{
			TextureMenager::LoadTexture("Textures/Chessboard/1.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/2.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/3.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/4.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/5.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/6.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/7.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/8.png")
		};

		SDL_Texture* letter_tags[8] =
		{
			TextureMenager::LoadTexture("Textures/Chessboard/A.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/B.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/C.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/D.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/E.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/F.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/G.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/H.png")
		};
		// TEST
};
