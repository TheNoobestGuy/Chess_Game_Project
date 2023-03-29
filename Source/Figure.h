#pragma once

#include "GameEngine.h"

struct Field_ID
{
	int row;
	int col;
};

class Figure
{
	protected:
		Field_ID field_ID;
		bool color;
		int size;

		// Pick up
		static bool FigurePickedUp;
		bool picked_up;

		// Collisions
		SDL_Rect figure_rect;
		SDL_Rect motion_rect;

	public:
		Figure(Field_ID field_ID, bool color, int size);
		~Figure();

		// Possible plays
		std::vector<Field_ID> available_moves;

		// Figure features
		virtual void AvailableMoves() = 0;
		void ChangePosition(Field_ID field_ID);
		void PickUp();

		// Base functions
		void Update();
		void Render();

		// Properties
		Field_ID GetFieldID() { return field_ID; }
		bool GetColor() { return color; }

		SDL_Rect* GetMotionRect() { return &motion_rect;  }
		bool PickedUp() { return picked_up; }

		// ****************** TEST ******************
		void Delete();

// ****************** TEST TEXTURES ******************
		struct Texture
		{
			SDL_Texture* texture;
			SDL_Rect srcRect = GameEngine::CreateRectangle(0, 0, 64);
		};

		Texture pawns_textures[2] =
		{
			{ TextureMenager::LoadTexture("Textures/Figures/white_pawn.png") },
			{ TextureMenager::LoadTexture("Textures/Figures/black_pawn.png") }
		};
};

