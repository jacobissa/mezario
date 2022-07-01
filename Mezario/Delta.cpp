#include "Delta.h"

Delta::Delta(const PositionPtr& ptr_position) : Enemy(ptr_position, Cell::e_cell_enemy_delta, Cell::e_cell_enemy_shot_delta)
{
	time_for_explotion = rand() % 5;
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
		if ( timer == -1 )
		{
			timer = i_time_counter + time_for_explotion;
		}
		if ( timer - i_time_counter < 0 )
		{
			mb_is_shot_active = true;
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_previous->GetPosition());
		}
	}
	else
	{
		mb_is_shot_active = false;
	}
}

std::vector <PositionPtr> Delta::GetAllAroundPosition() const
{
	std::vector <PositionPtr> enemy_all_position;
	for ( Position psn : enemy_position->GetAllPosition() )
	{
		enemy_all_position.emplace_back(std::make_shared<Position>(psn));
	}
	return enemy_all_position;
}