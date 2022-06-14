#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"

class Player final : public Creature
{
public:
	Player(const PositionPtr& ptr_position);

public:
	PositionPtr GetNextPosition(const Action e_action) const;
	void StartShot();

};
using PlayerPtr = std::shared_ptr<Player>;

#endif // !PLAYER_H