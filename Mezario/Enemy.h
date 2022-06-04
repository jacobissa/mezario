#ifndef ENEMY_H
#define ENEMY_H

#include "Creature.h"

class Enemy final : public Creature
{
public:
	Enemy(PositionPtr& ptr_position);

};
using EnemyPtr = std::shared_ptr<Enemy>;

#endif // !ENEMY_H