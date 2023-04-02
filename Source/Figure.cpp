#include "Figure.h"

Figure::Figure(int ID, Field_ID field_ID, bool color, int size)
{
	this->ID = ID;
	this->field_ID = field_ID;
	this->color = color;
	this->size = size;

	this->en_passant_attack = 0;
	this->first_move = true;
	this->picked_up = false;

	this->figure_rect = GameEngine::CreateRectangle(field_ID.x, field_ID.y, size);
	this->motion_rect = GameEngine::CreateRectangle(0, 0, size);
}

Figure::~Figure() {}

bool Figure::FigurePickedUp = false;

void Figure::ChangePosition(Field_ID field_ID)
{
	this->field_ID = field_ID;

	figure_rect.x = field_ID.x * size;
	figure_rect.y = field_ID.y * size;

	if (this->first_move)
	{
		this->first_move = false;
	}
}

void Figure::PickUp()
{
	if (GameEngine::CollisionDetector(GameEngine::mouse_x, GameEngine::mouse_y, &figure_rect) && GameEngine::mouse_left && !FigurePickedUp)
	{
		picked_up = true;
		FigurePickedUp = true;
	}
	else if (picked_up && !GameEngine::mouse_left && FigurePickedUp)
	{
		picked_up = false;
		FigurePickedUp = false;
	}

	if (picked_up)
	{
		motion_rect.x = GameEngine::mouse_x - (size / 2);
		motion_rect.y = GameEngine::mouse_y - (size / 2);
	}
}

// ****************** TEST ******************
void Figure::Delete()
{
	this->field_ID = { -1, -1 };
	this->picked_up = false;

	this->figure_rect = GameEngine::CreateRectangle(0, 0, 0);
	this->motion_rect = GameEngine::CreateRectangle(0, 0, 0);
}

