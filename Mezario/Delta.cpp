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
	const bool b_time_shot = (i_time_counter - mi_time_last_shot) > 3;
	if ( b_player_is_near && b_time_shot )
	{
		if ( ptr_position_player->x == mptr_position_current->x && ptr_position_player->y < mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetDownPosition());
		}
		else if ( ptr_position_player->x == mptr_position_current->x && ptr_position_player->y > mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetUpPosition());
		}
		else if ( ptr_position_player->x < mptr_position_current->x && ptr_position_player->y == mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetRightPosition());
		}
		else if ( ptr_position_player->x > mptr_position_current->x && ptr_position_player->y == mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetLeftPosition());
		}
		else if ( ptr_position_player->x > mptr_position_current->x && ptr_position_player->y < mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_previous->GetRightUpPosition());
		}
		else if ( ptr_position_player->x > mptr_position_current->x && ptr_position_player->y > mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_previous->GetRightDownPosition());
		}
		else if ( ptr_position_player->x < mptr_position_current->x && ptr_position_player->y > mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_previous->GetLeftDownPosition());
		}
		else if ( ptr_position_player->x < mptr_position_current->x && ptr_position_player->y < mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_previous->GetLeftUpPosition());
		}
		else
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_previous->GetPosition());
		}

		mi_time_last_shot = i_time_counter;
	}
	else
	{
		mb_is_shot_active = false;
	}
}