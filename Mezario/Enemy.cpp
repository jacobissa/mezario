#include "Enemy.h"

Enemy::Enemy(PositionPtr& ptr_position)
	: Creature(ptr_position , Cell::e_cell_enemy , { Cell::e_cell_enemy_shot_up, Cell::e_cell_enemy_shot_down, Cell::e_cell_enemy_shot_left_right, Cell::e_cell_enemy_shot_left_right })
{
}

PositionPtr Enemy::GetNextPosition()
{
	return 	std::make_shared<Position>(mptr_position_current->GetRandomNeighbourPosition());
}
