#include "Alpha.h"


Alpha::Alpha(PositionPtr& ptr_position )
	: Enemy(ptr_position, Cell::e_cell_enemy_alpha, { Cell::e_cell_enemy_shot_up, Cell::e_cell_enemy_shot_down, Cell::e_cell_enemy_shot_left_right, Cell::e_cell_enemy_shot_left_right })
{
}

PositionPtr Alpha::GetNextPosition(const PositionPtr& ptr_position_player) 
{
	if (mptr_position_current->IsClose(ptr_position_player->GetPosition(), 5))
	{
		if (mptr_position_current->GetPosition().x > ptr_position_player->GetPosition().x )
		{
			if (mptr_position_current->GetLeftPosition().x != Cell::e_cell_wall && 
				!mptr_position_current->IsClose(ptr_position_player->GetPosition(), 2))
			{
				return std::make_shared<Position>(mptr_position_current->GetLeftPosition());
			}
			else if(mptr_position_current->IsClose(ptr_position_player->GetPosition(), 2))
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
			else if(mptr_position_current->IsClose(ptr_position_player->GetPosition(), 2))
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
			else if(mptr_position_current->IsClose(ptr_position_player->GetPosition(), 2))
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
			else if(mptr_position_current->IsClose(ptr_position_player->GetPosition(), 2))
			{
				return  std::make_shared<Position>(mptr_position_current->GetPosition());
			}
		}

	}
	
		return 	std::make_shared<Position>(mptr_position_current->GetRandomNeighbourPosition());
}

