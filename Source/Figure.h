#pragma once

#include "Chessboard.h"

class Figure : protected Chessboard
{
	public:
		Figure() {};
		~Figure() {};

		virtual void Update() = 0;
		virtual void Render() = 0;
		
		// Properties
		SDL_Rect* RectGetter() { return &destRect; }
		void InMotionSetter(bool in_motion) { this->in_motion = in_motion; };

	protected:
		// Attributes
		int row_pos;
		int column_pos;
		int color;
		int set;

		bool in_motion;
		bool picked_up;
		bool putted_back;

		// Move handler
		std::vector<std::tuple<int, int, SDL_Rect>> possible_moves;
		std::stack<std::tuple<int, int, SDL_Rect>> move;

		// Textures
		SDL_Rect srcRect, destRect;

		SDL_Texture* pawns_textures[2][1] =
		{
			{ TextureMenager::LoadTexture("Textures/Figures/white_pawn.png") },
			{ TextureMenager::LoadTexture("Textures/Figures/black_pawn.png") }
		};

};

