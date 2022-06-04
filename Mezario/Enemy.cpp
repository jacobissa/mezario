#include "Enemy.h"

Enemy::Enemy(PositionPtr ptr_position)
	: Creature(ptr_position)
{
	me_cell = Cell::e_cell_enemy;
}