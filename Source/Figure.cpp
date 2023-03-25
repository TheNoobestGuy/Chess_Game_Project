#pragma once

#include "Figure.h"

Figure::Figure(int row_pos, int column_pos, int color, int set)
{
	this->row_pos = row_pos;
	this->column_pos = column_pos;
	this->color = color;
	this->set = set;
}

Figure::~Figure() {}
