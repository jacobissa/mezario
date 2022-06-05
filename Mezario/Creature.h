#ifndef CREATURE_H
#define CREATURE_H

#include "Mezario.h"

class Creature
{
public:
	Creature(PositionPtr& ptr_position);

public:
	enum Cell GetCell();
	const PositionPtr& GetCurrentPosition();
	const PositionPtr& GetPreviousPosition();
	void MoveTo(PositionPtr& ptr_position);

protected:
	enum Cell me_cell = Cell::e_cell_blank;
	PositionPtr mptr_position_current;

private:
	PositionPtr mptr_position_previous;
};
using CreaturePtr = std::shared_ptr<Creature>;

#endif // !CREATURE_H