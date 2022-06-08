#pragma once

#include "Enemy.h"
#include "Player.h"
#include "Position.h"

class Alpha final : public Enemy
{
public:
	Alpha(PositionPtr & ptr_position);

public:
	PositionPtr GetNextPosition(const PositionPtr& ptr_postion_player);
	

};
using AlphaPtr = std::shared_ptr<Alpha>;


