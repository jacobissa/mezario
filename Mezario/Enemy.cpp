#include "Enemy.h"

Enemy::Enemy(PositionPtr& ptr_position, enum Cell e_cell_creature, const CellShot s_cell_shot)
	: Creature(ptr_position, e_cell_creature, s_cell_shot)
{
}

PositionPtr Enemy::GetNextPosition(const PositionPtr& ptr_position_player)
{
	return 	std::make_shared<Position>(mptr_position_current->GetPosition());
}

