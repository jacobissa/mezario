#include "Player.h"

Player::Player(PositionPtr ptr_position)
	: Creature(ptr_position)
{
	me_cell = Cell::e_cell_player;
}