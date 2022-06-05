#include "Player.h"

Player::Player(PositionPtr& ptr_position)
	: Creature(ptr_position)
{
	me_cell = Cell::e_cell_player;
	me_cell_shot = Cell::e_cell_player_shot;
}

PositionPtr Player::GetNextPosition(enum Action e_action)
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