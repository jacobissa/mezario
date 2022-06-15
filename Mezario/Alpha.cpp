#include "Alpha.h"


Alpha::Alpha(PositionPtr& ptr_position)
	: Enemy(ptr_position, Cell::e_cell_enemy_alpha, { Cell::e_cell_enemy_shot_alpha, Cell::e_cell_enemy_shot_alpha, Cell::e_cell_enemy_shot_alpha, Cell::e_cell_enemy_shot_alpha })
{
}

PositionPtr Alpha::GetNextPosition(const PositionPtr& ptr_position_player)
{
	if (mptr_position_current->IsClose(ptr_position_player->GetPosition(), 10))
	{
		if (mptr_position_current->GetPosition().x > ptr_position_player->GetPosition().x)
		{
			if (mptr_position_current->GetLeftPosition().x != Cell::e_cell_wall &&
				!mptr_position_current->IsClose(ptr_position_player->GetPosition(), 2))
			{
				return std::make_shared<Position>(mptr_position_current->GetLeftPosition());
			}
			else if (mptr_position_current->IsClose(ptr_position_player->GetPosition(), 2))
			{
				return std::make_shared<Position>(mptr_position_current->GetPosition());
			}
		}
		else if (mptr_position_current->GetPosition().x < ptr_position_player->GetPosition().x)
		{
			if (mptr_position_current->GetRightPosition().x != Cell::e_cell_wall &&
				!mptr_position_current->IsClose(ptr_position_player->GetPosition(), 2))
			{
				return  std::make_shared<Position>(mptr_position_current->GetRightPosition());
			}
			else if (mptr_position_current->IsClose(ptr_position_player->GetPosition(), 2))
			{
				return  std::make_shared<Position>(mptr_position_current->GetPosition());
			}
		}
		else if (mptr_position_current->GetPosition().y < ptr_position_player->GetPosition().y)
		{
			if (mptr_position_current->GetDownPosition().y != Cell::e_cell_wall &&
				!mptr_position_current->IsClose(ptr_position_player->GetPosition(), 2))
			{
				return  std::make_shared<Position>(mptr_position_current->GetDownPosition());
			}
			else if (mptr_position_current->IsClose(ptr_position_player->GetPosition(), 2))
			{
				return  std::make_shared<Position>(mptr_position_current->GetPosition());
			}
		}
		else if (mptr_position_current->GetPosition().y > ptr_position_player->GetPosition().y)
		{
			if (mptr_position_current->GetUpPosition().y != Cell::e_cell_wall &&
				!mptr_position_current->IsClose(ptr_position_player->GetPosition(), 2))
			{
				return  std::make_shared<Position>(mptr_position_current->GetUpPosition());
			}
			else if (mptr_position_current->IsClose(ptr_position_player->GetPosition(), 2))
			{
				return  std::make_shared<Position>(mptr_position_current->GetPosition());
			}
		}
	}
	return 	std::make_shared<Position>(mptr_position_current->GetPosition());
}


void Alpha::StartShot(const PositionPtr& ptr_position_player, const int i_time_counter)
{
	const bool b_player_is_near = mptr_position_current->IsClose(ptr_position_player->GetPosition(), 5);
	const bool b_time_shot = std::abs(i_time_counter - mi_time_last_shot) > 0;
	if (b_player_is_near && b_time_shot)
	{
		mb_is_shot_active = true;
		if (ptr_position_player->x == mptr_position_current->x && ptr_position_player->y < mptr_position_current->y)
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetDownPosition());
		}
		else if (ptr_position_player->x == mptr_position_current->x && ptr_position_player->y > mptr_position_current->y)
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetUpPosition());
		}
		else if (ptr_position_player->x < mptr_position_current->x && ptr_position_player->y == mptr_position_current->y)
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetRightPosition());
		}
		else if (ptr_position_player->x > mptr_position_current->x && ptr_position_player->y == mptr_position_current->y)
		{
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
			mptr_position_shot_previous = std::make_shared<Position>(mptr_position_current->GetLeftPosition());
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