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

void Position::UpdatePosition(const Position position)
{
	this->x = position.x;
	this->y = position.y;
}

bool Position::Equals(const Position& position) const
{
	return ( this->x == position.x && this->y == position.y );
}

bool Position::IsClose(const Position& position , const int i_allowed_distance) const
{
	return ( std::abs(this->x - position.x) <= i_allowed_distance && std::abs(this->y - position.y) <= i_allowed_distance );
}


Position Position::GetPosition() const
{
	return *this;
}

Position Position::GetUpPosition() const
{
	return Position(x , y - 1);
}

Position Position::GetDownPosition() const
{
	return Position(x , y + 1);
}

Position Position::GetLeftPosition() const
{
	return Position(x - 1 , y);
}

Position Position::GetRightPosition() const
{
	return Position(x + 1 , y);
}

Position Position::GetRightUpPosition() const
{
	return Position(x + 1, y - 1);
}

Position Position::GetRightDownPosition() const
{
	return Position(x + 1, y + 1);
}

Position Position::GetLeftDownPosition() const
{
	return Position(x - 1, y + 1);
}

Position Position::GetLeftUpPosition() const
{
	return Position(x - 1, y - 1);
}

std::vector<Position> Position::GetAllPosition() const
{
	std::vector<Position> all_position;
	all_position.emplace_back(GetUpPosition());
	all_position.emplace_back(GetDownPosition()); 
	all_position.emplace_back(GetRightPosition()); 
	all_position.emplace_back(GetLeftPosition()); 
	all_position.emplace_back(GetLeftUpPosition()); 
	all_position.emplace_back(GetRightUpPosition()); 
	all_position.emplace_back(GetLeftDownPosition()); 
	all_position.emplace_back(GetRightDownPosition()); 
	return all_position;
}

Position Position::GetRandomNeighbourPosition() const
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
