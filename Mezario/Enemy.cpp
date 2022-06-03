#include "Enemy.h"

Enemy::Enemy(Position position)
	: Creature(position)
{
	me_cell = Cell::e_cell_enemy;
}