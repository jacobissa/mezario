#ifndef ENEMY_H
#define ENEMY_H

#include "Creature.h"
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
class Enemy : public Creature
{
public:
	Enemy(PositionPtr& ptr_position, enum Cell e_cell_creature, const CellShot s_cell_shot);

public:
	PositionPtr GetNextPosition(const PositionPtr& ptr_position_player);

};
using EnemyPtr = std::shared_ptr<Enemy>;

#endif // !ENEMY_H