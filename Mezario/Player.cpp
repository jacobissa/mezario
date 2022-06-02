#include "Player.h"

Player::Player(Position position)
	: m_position_current(position)
{
}

Position Player::GetCurrentPosition()
{
	return m_position_current;
}
