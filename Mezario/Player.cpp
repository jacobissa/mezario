#include "Player.h"

Player::Player(Position position)
	: Creature(position)
{
	me_cell = Cell::e_cell_player;
}