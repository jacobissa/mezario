#include "Gamma.h"

Gamma::Gamma(const PositionPtr& ptr_position) : Enemy(ptr_position, Cell::e_cell_enemy_gamma, { Cell::e_cell_enemy_shot_gamma })
{
}

PositionPtr Gamma::GetNextPosition(const PositionPtr& ptr_position, const int i_timer_counter)
{
	return 	std::make_shared<Position>(mptr_position_current->GetPosition());
}

void Gamma::StartShot(const PositionPtr& ptr_position, const int i_time_counter)
{
	const bool b_time_shot = (i_time_counter - mi_time_last_shot) > 0;
	if ( b_time_shot )
	{
		mb_is_shot_active = true;
		mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
		mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetRandomNeighbourPosition());
	}
}



