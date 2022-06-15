#pragma once

#include "Enemy.h"
#include "Player.h"
#include "Position.h"

class Alpha final : public Enemy
{
public:
	Alpha(PositionPtr & ptr_position);

public:
	PositionPtr GetNextPosition(const PositionPtr& ptr_postion_player) override;
	void StartShot(const PositionPtr& ptr_position_player, const int i_time_counter) override;
	

};
using AlphaPtr = std::shared_ptr<Alpha>;


