#ifndef POSITION_H
#define POSITION_H

#include <memory>
#include <vector>

struct Position
{
	int x;
	int y;

	Position(const int x , const int y);

	void UpdatePosition(const int x , const int y);
	void UpdatePosition(const Position position);
	bool Equals(const Position& position) const;
	bool IsClose(const Position& position , const int i_allowed_distance) const;

	Position GetPosition() const;
	Position GetUpPosition() const;
	Position GetDownPosition() const;
	Position GetLeftPosition() const;
	Position GetRightPosition() const;
	Position GetRightUpPosition() const;
	Position GetRightDownPosition() const;
	Position GetLeftDownPosition() const;
	Position GetLeftUpPosition() const;
	Position GetRandomNeighbourPosition() const;
	std::vector<Position> GetAllPosition() const;
};
using PositionPtr = std::shared_ptr<Position>;

#endif // !POSITION_H