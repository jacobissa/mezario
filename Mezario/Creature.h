#pragma once
#include "Mezario.h"

class Creature
{
public:
	Creature(Position position);

public:
	enum Cell GetCell();
	Position GetCurrentPosition();
	Position GetPreviousPosition();
	void MoveTo(Position position);

protected:
	enum Cell me_cell = Cell::e_cell_blank;

private:
	Position m_position_current;
	Position m_position_previous;
};
using CreaturePtr = std::shared_ptr<Creature>;

