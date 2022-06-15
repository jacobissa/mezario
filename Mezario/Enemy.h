#ifndef ENEMY_H
#define ENEMY_H

#include "Creature.h"

class Enemy : public Creature
{
public:
	Enemy(PositionPtr& ptr_position, const Cell e_cell_creature, const CellShot s_cell_shot);

public:
	virtual PositionPtr GetNextPosition(const PositionPtr& ptr_position_player) = 0;
	virtual void StartShot(const PositionPtr& ptr_position_player, const int i_time_counter) = 0;

protected:
	int mi_time_last_shot = -1;
};
using EnemyPtr = std::shared_ptr<Enemy>;

#endif // !ENEMY_H