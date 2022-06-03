#pragma once
#include "Mezario.h"

class Creature
{
public:
	Creature(Position position);

public:
	Position GetCurrentPosition();
	Position GetPreviousPosition();
	void MoveTo(Position position);

private:
	Position m_position_current;
	Position m_position_previous;
};

