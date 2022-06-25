#include "Delta.h"

Delta::Delta(const PositionPtr& ptr_position) : Enemy(ptr_position, Cell::e_cell_enemy_delta, Cell::e_cell_enemy_shot_delta)
{

}

PositionPtr Delta::GetNextPosition(const PositionPtr& ptr_position_player, const int i_time_counter)
{
	return 	std::make_shared<Position>(mptr_position_current->GetPosition());
}

void Delta::StartShot(const PositionPtr& ptr_position_player, const int i_time_counter)
{
	const bool b_player_is_near = mptr_position_current->IsClose(ptr_position_player->GetPosition(), 5);

	if ( b_player_is_near )
	{
		timer = i_time_counter + time_for_explotion;
		if ( timer - i_time_counter == 0 )
		{
			mb_is_shot_active = true;

		}
	}
	else
	{
		mb_is_shot_active = false;
	}
}