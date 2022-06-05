#include "Enemy.h"

Enemy::Enemy(PositionPtr& ptr_position)
	: Creature(ptr_position)
{
	me_cell = Cell::e_cell_enemy;
	me_cell_shot = e_cell_enemy_shot;
}

PositionPtr Enemy::GetNextPosition()
{
	return 	std::make_shared<Position>(mptr_position_current->GetRandomNeighbourPosition());
}
