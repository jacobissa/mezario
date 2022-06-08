#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"

class Player final : public Creature
{
public:
	Player(PositionPtr& ptr_position);

public:
	PositionPtr GetNextPosition(enum Action e_action);
	void DestroyPlayer();

};
using PlayerPtr = std::shared_ptr<Player>;

#endif // !PLAYER_H