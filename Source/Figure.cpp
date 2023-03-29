#include "Figure.h"

Figure::Figure(Field_ID field_ID, bool color, int size)
{
	this->field_ID = field_ID;
	this->color = color;
	this->size = size;

	this->picked_up = false;

	this->figure_rect = GameEngine::CreateRectangle(field_ID.row, field_ID.col, size);
	this->motion_rect = GameEngine::CreateRectangle(0, 0, size);
}

Figure::~Figure() {}

bool Figure::FigurePickedUp = false;


void Figure::ChangePosition(Field_ID field_ID)
{
	this->field_ID = field_ID;

	figure_rect.x = field_ID.row * size;
	figure_rect.y = field_ID.col * size;
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

void Figure::Update()
{
	AvailableMoves();
	PickUp();
}

void Figure::Render()
{
	if (picked_up)
		TextureMenager::Draw(pawns_textures[color].texture, pawns_textures[color].srcRect, motion_rect);
	else
		TextureMenager::Draw(pawns_textures[color].texture, pawns_textures[color].srcRect, figure_rect);
}

// Pure virtual
void Figure::AvailableMoves() {}


// ****************** TEST ******************
void Figure::Delete()
{
	this->field_ID = { -1, -1 };
	this->picked_up = false;

	this->figure_rect = GameEngine::CreateRectangle(0, 0, 0);
	this->motion_rect = GameEngine::CreateRectangle(0, 0, 0);
}

