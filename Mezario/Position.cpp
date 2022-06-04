#include "Position.h"

Position::Position(int x , int y)
{
	this->x = x;
	this->y = y;
}


void Position::UpdatePosition(int x , int y)
{
	this->x = x;
	this->y = y;
}

bool Position::Equals(Position position)
{
	return ( this->x == position.x && this->y == position.y );
}

bool Position::IsClose(Position position)
{
	return ( std::abs(this->x - position.x) <= 5 && std::abs(this->y - position.y) <= 5 );
}


Position Position::GetPosition()
{
	return *this;
}

Position Position::GoLeft()
{
	x--;
	return *this;
}

Position Position::GoRight()
{
	x++;
	return *this;
}

Position Position::GoUp()
{
	y--;
	return *this;
}

Position Position::GoDown()
{
	y++;
	return *this;
}

Position Position::GoRandom()
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

Position Position::GetRandomnNeighbour()
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
