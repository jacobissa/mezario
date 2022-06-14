#include "Player.h"

Player::Player(const PositionPtr& ptr_position)
	: Creature(ptr_position , Cell::e_cell_player , { Cell::e_cell_player_shot_up, Cell::e_cell_player_shot_down, Cell::e_cell_player_shot_left, Cell::e_cell_player_shot_right })
{
}

PositionPtr Player::GetNextPosition(const Action e_action) const
{
	switch ( e_action )
	{
		case Action::e_action_up:
			{
				return std::make_shared<Position>(mptr_position_current->GetUpPosition());
			}
			break;
		case Action::e_action_down:
			{
				return std::make_shared<Position>(mptr_position_current->GetDownPosition());
			}
			break;
		case Action::e_action_left:
			{
				return std::make_shared<Position>(mptr_position_current->GetLeftPosition());
			}
			break;
		case Action::e_action_right:
			{
				return std::make_shared<Position>(mptr_position_current->GetRightPosition());
			}
			break;
		default:
			break;
	}
	return nullptr;
}

void Player::StartShot()
{
	if ( mptr_position_current->Equals(mptr_position_previous->GetPosition()) )
	{
		mb_is_shot_active = false;
		// creature, who didn't move yet, can't start shooting
	}
	else
	{
		mb_is_shot_active = true;
		mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
		mptr_position_shot_previous = std::make_shared<Position>(mptr_position_previous->GetPosition());
	}
}