#ifndef POSITION_H
#define POSITION_H

#include "Mezario.h"

struct Position
{
	int x;
	int y;

	Position(const int x , const int y);

	void UpdatePosition(const int x , const int y);
	void UpdatePosition(Position position);
	bool Equals(const Position& position);
	bool IsClose(const Position& position , const int i_allowed_distance);

	Position GetPosition();
	Position GetUpPosition();
	Position GetDownPosition();
	Position GetLeftPosition();
	Position GetRightPosition();
	Position GetRandomNeighbourPosition();
};
using PositionPtr = std::shared_ptr<Position>;

#endif // !POSITION_H