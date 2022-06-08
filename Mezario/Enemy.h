#ifndef ENEMY_H
#define ENEMY_H

#include "Creature.h"

class Enemy : public Creature
{
public:
	Enemy(PositionPtr& ptr_position, enum Cell e_cell_creature, const CellShot s_cell_shot);

public:
	PositionPtr GetNextPosition(const PositionPtr& ptr_position_player);
	virtual void StartShot(const PositionPtr& ptr_postion_player) = 0;
};
using EnemyPtr = std::shared_ptr<Enemy>;

#endif // !ENEMY_H