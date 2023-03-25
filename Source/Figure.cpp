#pragma once

#include "Figure.h"

Figure::Figure(int row_pos, int column_pos, int color, int set)
{
	this->row_pos = row_pos;
	this->column_pos = column_pos;
	this->color = color;
	this->set = set;

	// Source size and position of image
	srcRect.w = 462;
	srcRect.h = 595;
	srcRect.x = srcRect.y = 0;

	// Desired size of image
	destRect.w = destRect.h = 64;
}

Figure::~Figure() {}

bool Figure::MouseColliding(int mouse_x, int mouse_y, SDL_Rect rect)
{
	if (mouse_x >= rect.x && mouse_x <= (rect.x + rect.w))
	{
		if (mouse_y >= rect.y && mouse_y <= (rect.y + rect.h)) {
			return true;
		}
	}
	return false;
}

SDL_Rect Figure::RectGetter()
{
	return destRect;
}

void Figure::InMotionSetter(bool in_motion)
{
	this->in_motion = in_motion;
}
