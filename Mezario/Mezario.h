#pragma once
#include <iostream>

struct Position
{
	int x;
	int y;
};

enum Cell : char
{
	e_cell_blank = ' ' ,
	e_cell_wall = '#' ,
	e_cell_player = '@' ,
};