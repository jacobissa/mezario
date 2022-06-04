#ifndef POSITION_H
#define POSITION_H

#include "Mezario.h"

struct Position
{
	int x;
	int y;

	Position(int x , int y);

	void UpdatePosition(int x , int y);
	bool Equals(Position position);
	bool IsClose(Position position);

	Position GetPosition();
	Position GoLeft();
	Position GoRight();
	Position GoUp();
	Position GoDown();
	Position GoRandom();
	Position GetRandomnNeighbour();
};
using PositionPtr = std::shared_ptr<Position>;

#endif // !POSITION_H