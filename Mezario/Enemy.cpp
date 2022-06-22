#include "Enemy.h"

Enemy::Enemy(const PositionPtr& ptr_position, const Cell e_cell_enemy, const Cell e_cell_shot)
	: Creature(ptr_position, e_cell_enemy, { e_cell_shot ,e_cell_shot ,e_cell_shot ,e_cell_shot })
{
}
