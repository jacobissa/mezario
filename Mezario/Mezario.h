#ifndef MEZARIO_H
#define MEZARIO_H

#include <iostream>
#include <Windows.h>
#include <vector>


struct Position
{
	int x;
	int y;

	Position(int x , int y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(Position position)
	{
		return ( position.x == x && position.y == y );
	}

	Position GoLeft()
	{
		x--;
		return *this;
	}
	Position GoRight()
	{
		x++;
		return *this;
	}
	Position GoUp()
	{
		y--;
		return *this;
	}
	Position GoDown()
	{
		y++;
		return *this;
	}
	Position GoRandom()
	{
		switch ( rand() % 4 )
		{
			case 0:
				{
					x++;
				}
				break;
			case 1:
				{
					x--;
				}
				break;
			case 2:
				{
					y++;
				}
				break;
			case 3:
				{
					y--;
				}
				break;
		}
		return *this;
	}
	Position GetRandomnNeighbour()
	{
		switch ( rand() % 4 )
		{
			case 0:
				{
					return Position(x + 1 , y);
				}
				break;
			case 1:
				{
					return Position(x - 1 , y);
				}
				break;
			case 2:
				{
					return Position(x , y + 1);
				}
				break;
			case 3:
				{
					return Position(x , y - 1);
				}
				break;
		}
		return *this;
	}
};

enum Cell : char
{
	e_cell_blank = ' ' ,
	e_cell_wall = '#' ,
	e_cell_player = '@' ,
	e_cell_enemy = '%' ,
};

#endif // !MEZARIO_H