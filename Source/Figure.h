#pragma once

#include "GameEngine.h"
#include "TextureMenager.h"
#include "Chessboard.h"

class Figure : protected Chessboard
{
	public:
		Figure(int row_pos, int column_pos, int color, int set);
		~Figure();

		virtual void Update() = 0;
		virtual void Render() = 0;

	protected:
		int row_pos;
		int column_pos;
		int color;
		int set;

		virtual void MovesList() = 0;

		// Textures
		SDL_Rect srcRect, destRect;

		SDL_Texture* pawns_textures[2][1] =
		{
			{ TextureMenager::LoadTexture("Textures/Figures/pawn.png") },
			{ TextureMenager::LoadTexture("Textures/Figures/pawn.png") }
		};

};

