#include "Player.h"

Player::Player(PositionPtr& ptr_position)
	: Creature(ptr_position)
{
	me_cell = Cell::e_cell_player;
}

PositionPtr Player::GetNextPosition(enum Action e_action)
{
	switch ( e_action )
	{
		case e_action_up:
			{
				return std::make_shared<Position>(mptr_position_current->GetUpPosition());
			}
			break;
		case e_action_down:
			{
				return std::make_shared<Position>(mptr_position_current->GetDownPosition());
			}
			break;
		case e_action_left:
			{
				return std::make_shared<Position>(mptr_position_current->GetLeftPosition());
			}
			break;
		case e_action_right:
			{
				return std::make_shared<Position>(mptr_position_current->GetRightPosition());
			}
			break;
		default:
			break;
	}
	return nullptr;
}
