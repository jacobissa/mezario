#include "Beta.h"

Beta::Beta(const PositionPtr& ptr_position) : Enemy(ptr_position, Cell::e_cell_enemy_beta, Cell::e_cell_enemy_shot_beta )
{
}

PositionPtr Beta::GetNextPosition(const PositionPtr& ptr_position_player, const int i_time_counter)
{
	const bool b_player_is_near = mptr_position_current->IsClose(ptr_position_player->GetPosition(), 10);
	const bool b_time_move = (i_time_counter - mi_time_last_move) > 0;
	if ( b_player_is_near && b_time_move )
	{
		mi_time_last_move = i_time_counter;
		if ( mptr_position_current->GetPosition().x < ptr_position_player->GetPosition().x 
			&& mptr_position_current->GetPosition().y > ptr_position_player->GetPosition().y)
		{
			
			return std::make_shared<Position>(mptr_position_current->GetRightUpPosition());
		
		}
		else if ( mptr_position_current->GetPosition().x < ptr_position_player->GetPosition().x 
				 && mptr_position_current->GetPosition().y < ptr_position_player->GetPosition().y )
		{
			
			return  std::make_shared<Position>(mptr_position_current->GetRightDownPosition());
			
		}
		else if ( mptr_position_current->GetPosition().x > ptr_position_player->GetPosition().x 
				 && mptr_position_current->GetPosition().y < ptr_position_player->GetPosition().y )
		{
			
			return  std::make_shared<Position>(mptr_position_current->GetLeftDownPosition());
			
		}
		else if ( mptr_position_current->GetPosition().x > ptr_position_player->GetPosition().x && mptr_position_current->GetPosition().y > ptr_position_player->GetPosition().y )
		{
			
				return  std::make_shared<Position>(mptr_position_current->GetLeftUpPosition());
			
		}
		
	}
	return 	std::make_shared<Position>(mptr_position_current->GetPosition());
}

void Beta::StartShot(const PositionPtr& ptr_position_player, const int i_time_counter)
{
	const bool b_player_is_near = mptr_position_current->IsClose(ptr_position_player->GetPosition(), 1);
	const bool b_time_shot = (i_time_counter - mi_time_last_shot) > 0;
	if ( b_player_is_near && b_time_shot )
	{
		mb_is_shot_active = true;
		if ( ptr_position_player->x == mptr_position_current->x && ptr_position_player->y < mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetUpPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetUpPosition());
		}
		else if ( ptr_position_player->x == mptr_position_current->x && ptr_position_player->y > mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetDownPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetDownPosition());
		}
		else if ( ptr_position_player->x < mptr_position_current->x && ptr_position_player->y == mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetLeftPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetLeftPosition());
		}
		else if ( ptr_position_player->x > mptr_position_current->x && ptr_position_player->y == mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetRightPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetRightPosition());
		}
		else if ( ptr_position_player->x > mptr_position_current->x && ptr_position_player->y < mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetRightUpPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetRightUpPosition());
		}
		else if ( ptr_position_player->x > mptr_position_current->x && ptr_position_player->y > mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetRightDownPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetRightDownPosition());
		}
		else if ( ptr_position_player->x < mptr_position_current->x && ptr_position_player->y > mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetLeftDownPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetLeftDownPosition());
		}
		else if ( ptr_position_player->x < mptr_position_current->x && ptr_position_player->y < mptr_position_current->y )
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetLeftUpPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetLeftUpPosition());
		}
		else
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetPosition());
		}

		mi_time_last_shot = i_time_counter;
	}
	else
	{
		mb_is_shot_active = false;
	}

}