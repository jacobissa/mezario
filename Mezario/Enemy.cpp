#include "Enemy.h"

Enemy::Enemy(const PositionPtr& ptr_position, const Cell e_cell_creature , const CellShot s_cell_shot)
	: Creature(ptr_position , e_cell_creature , s_cell_shot)
{
}
