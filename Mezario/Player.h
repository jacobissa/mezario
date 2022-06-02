#pragma once
#include "Mezario.h"

class Player
{
public:
	Player(Position position);

public:
	Position GetCurrentPosition();

private:
	Position m_position_current;
};

