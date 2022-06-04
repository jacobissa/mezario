#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"

class Player final : public Creature
{
public:
	Player(PositionPtr ptr_position);

};
using PlayerPtr = std::shared_ptr<Player>;

#endif // !PLAYER_H