#pragma once

#include "GameEngine.h"

class Figure
{
	protected:
		// Properties
		int ID;
		Field_ID field_ID;
		int color;
		int size;
		SDL_Texture* texture;

		// Movement
		static bool FigurePickedUp;
		bool first_move;
		bool picked_up;

		// Collisions
		SDL_Rect figure_rect;
		SDL_Rect motion_rect;

	public:
		Figure(int figure_ID, Field_ID field_ID, bool color, int size);
		~Figure();

		// Possible plays
		std::vector<Field_ID> available_moves;

		// Figure features
		virtual void AvailableMoves(Field* chessboard[8][8]) = 0;
		void ChangePosition(Field_ID field_ID);
		void PickUp();

		// Draw function
		virtual void Render() = 0;

		// Properties
		int GetFigureID() { return ID; }
		Field_ID GetFieldID() { return field_ID; }

		bool GetColor() { return color; }

		SDL_Rect* GetMotionRect() { return &motion_rect;  }
		bool PickedUp() { return picked_up; }

		// ****************** TEST ******************
		void Delete();
};
