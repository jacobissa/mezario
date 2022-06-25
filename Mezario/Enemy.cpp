#include "Enemy.h"
#include <iostream>

Enemy::Enemy(const PositionPtr& ptr_position, const Cell e_cell_enemy, const Cell e_cell_shot)
	: Creature(ptr_position, e_cell_enemy, { e_cell_shot ,e_cell_shot ,e_cell_shot ,e_cell_shot })
{
	enemy_position = ptr_position;
	e_cell_enemy_type = e_cell_enemy;
}

const Cell Enemy::GetEnemyType()
{
	return e_cell_enemy_type;
}

std::vector <PositionPtr> Enemy::GetAllAroundPosition() const
{
	std::vector <PositionPtr> enemy_all_position;
	for( Position psn : enemy_position->GetAllPosition() )
	{
		enemy_all_position.emplace_back(std::make_shared<Position>(psn));
	}
	return enemy_all_position;
}
