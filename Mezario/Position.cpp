#include "Position.h"

Position::Position(const int x , const int y)
{
	this->x = x;
	this->y = y;
}


void Position::UpdatePosition(const int x , const int y)
{
	this->x = x;
	this->y = y;
}

void Position::UpdatePosition(Position position)
{
	this->x = position.x;
	this->y = position.y;
}

bool Position::Equals(const Position& position)
{
	return ( this->x == position.x && this->y == position.y );
}

bool Position::IsClose(const Position& position, const int i_allowed_distance)
{
	return ( std::abs(this->x - position.x) <= i_allowed_distance && std::abs(this->y - position.y) <= i_allowed_distance );
}


Position Position::GetPosition()
{
	return *this;
}

Position Position::GetUpPosition()
{
	return Position(x , y - 1);
}

Position Position::GetDownPosition()
{
	return Position(x , y + 1);
}

Position Position::GetLeftPosition()
{
	return Position(x - 1 , y);
}

Position Position::GetRightPosition()
{
	return Position(x + 1 , y);
}

Position Position::GetRandomNeighbourPosition()
{
	switch ( rand() % 4 )
	{	
		case 0:
			{
				return GetUpPosition();
			}
			break;
		case 1:
			{
				return GetDownPosition();
			}
			break;
		case 2:
			{
				return GetLeftPosition();
			}
			break;
		case 3:
			{
				return GetRightPosition();
			}
			break;
	}
	return GetPosition();
}
