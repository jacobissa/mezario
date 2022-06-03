#include "Creature.h"

Creature::Creature(Position position)
	: m_position_current(position)
	, m_position_previous(position)
{
}

Position Creature::GetCurrentPosition()
{
	return m_position_current;
}

Position Creature::GetPreviousPosition()
{
	return m_position_previous;
}

void Creature::MoveTo(Position position)
{
	m_position_previous = m_position_current;
	m_position_current = position;
}
