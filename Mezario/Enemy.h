#ifndef ENEMY_H
#define ENEMY_H

#include "Creature.h"
#include <vector>

class Enemy : public Creature
{
public:
	Enemy(const PositionPtr& ptr_position, const Cell e_cell_enemy, const Cell e_cell_shot);

public:
	virtual PositionPtr GetNextPosition(const PositionPtr& ptr_position_player, const int i_time_counter) = 0;
	virtual void StartShot(const PositionPtr& ptr_position_player, const int i_time_counter) = 0;
	const Cell GetEnemyType();
	std::vector <PositionPtr> GetAllAroundPosition() const;

protected:
	PositionPtr enemy_position;
	Cell e_cell_enemy_type;
	int mi_time_last_shot = -1;
	int mi_time_last_move = -1;
};
using EnemyPtr = std::shared_ptr<Enemy>;

#endif // !ENEMY_H