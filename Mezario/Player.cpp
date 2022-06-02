#include "Player.h"

Player::Player(Position position)
	: m_position_current(position)
	, m_position_previous(position)
{
}

Position Player::GetCurrentPosition()
{
	return m_position_current;
}

Position Player::GetPreviousPosition()
{
	return m_position_previous;
}

void Player::MoveTo(Position position)
{
	m_position_previous = m_position_current;
	m_position_current = position;
}
