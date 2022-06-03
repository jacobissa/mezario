#pragma once
#include "Creature.h"

class Player final : public Creature
{
public:
	Player(Position position);

};
using PlayerPtr = std::shared_ptr<Player>;