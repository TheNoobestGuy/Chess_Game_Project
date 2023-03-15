#pragma once

#include "GameEngine.h"

class Chessboard
{
	public:
		Chessboard();
		~Chessboard();

		void LoadBoard();
		void DrawBoard();

	private:
		SDL_Rect src, dest;

		SDL_Texture* whiteSqr;
		SDL_Texture* blackSqr;

		int chessboard[8][8];
};

