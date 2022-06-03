#ifndef MEZARIO_H
#define MEZARIO_H

#include <iostream>
#include <Windows.h>


struct Position
{
	int x;
	int y;

	Position(int x , int y)
	{
		this->x = x;
		this->y = y;
	}

	inline bool operator==(Position position)
	{
		return ( position.x == x && position.y == y );
	}
};

enum Cell : char
{
	e_cell_blank = ' ' ,
	e_cell_wall = '#' ,
	e_cell_player = '@' ,
	e_cell_enemy = '%',
};

#endif // !MEZARIO_H