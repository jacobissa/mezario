#include "Creature.h"

Creature::Creature(PositionPtr& ptr_position)
	: mptr_position_current(ptr_position)
	, mptr_position_previous(ptr_position)
{
}

Cell Creature::GetCell()
{
	return me_cell;
}

const PositionPtr& Creature::GetCurrentPosition()
{
	return mptr_position_current;
}

const PositionPtr& Creature::GetPreviousPosition()
{
	return mptr_position_previous;
}

void Creature::MoveTo(PositionPtr& ptr_position)
{
	mptr_position_previous = mptr_position_current;
	mptr_position_current = ptr_position;
}
