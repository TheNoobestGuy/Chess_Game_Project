#pragma once

#include "GameEngine.h"
#include "TextureMenager.h"

struct Field
{
	int figure;
	char texture;
};

class Chessboard
{
	public:
		Chessboard();
		~Chessboard();	

		void DrawBoard();

	protected:

		Field chessboard[10][10] =
		{

					{ { 0, 0}, { 0, 'H'}, { 0, 'G'}, { 0, 'F'}, { 0, 'E'}, { 0, 'D'}, { 0, 'C'}, { 0, 'B'}, { 0, 'A'}, { 0, 0} },
					{ { 0, 1}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 8} },
					{ { 0, 2}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 7} },
					{ { 0, 3}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 6} },
					{ { 0, 4}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 5} },
					{ { 0, 5}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 4} },
					{ { 0, 6}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 3} },
					{ { 0, 7}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 2} },
					{ { 0, 8}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 'O'}, { 0, 'X'}, { 0, 1} },
					{ { 0, 0}, { 0, 'A'}, { 0, 'B'}, { 0, 'C'}, { 0, 'D'}, { 0, 'E'}, { 0, 'F'}, { 0, 'G'}, { 0, 'H'}, { 0, 0} }

		};

	private:

		// Textures
		SDL_Rect srcRect, destRect;

		SDL_Texture* fields_colors[2] =
		{
			TextureMenager::LoadTexture("Textures/Chessboard/whiteSqr.png"),
			TextureMenager::LoadTexture("Textures/Chessboard/blackSqr.png")
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

};
