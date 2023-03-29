#pragma once

#include "GameEngine.h"
#include "Pawn.h"

struct Field
{
	Field_ID field_ID;
	int field_size;
	bool color;

	Figure* figure;
	SDL_Rect field_rect = GameEngine::CreateRectangle(field_ID.row, field_ID.col, field_size);
};

class Chessboard
{
	private:
		int player;
		int fields_size;

		bool make_move;
		Field_ID move_to;
		bool moved_figure;

		Field chessboard[8][8];

		Figure* current_figure;
		Figure* white_player[8];
		Figure* black_player[8];

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
		void BoardTracer();
		void UpdateFigures();
		void RenderFigures();

		// Figures features
		void MoveFigure();
		void PickedUpFigure();


// ****************** TEST TEXTURES ******************
	private:
		struct Texture
		{
			SDL_Texture* texture;
			SDL_Rect srcRect = GameEngine::CreateRectangle(0, 0, 64);
		};

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
