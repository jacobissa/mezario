#ifndef BETA_H
#define BETA_H

#include "Enemy.h"
#include "Player.h"
#include "Position.h"

class Beta final : public Enemy
{
public:
	Beta(const PositionPtr& ptr_position);

public:
	PositionPtr GetNextPosition(const PositionPtr& ptr_postion_player, const int i_time_counter) override;
	void StartShot(const PositionPtr& ptr_position_player, const int i_time_counter) override;

};
using BetaPtr = std::shared_ptr<Beta>;

#endif