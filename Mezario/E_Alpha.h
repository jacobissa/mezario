#pragma once

#include "Enemy.h"
#include "Player.h"
#include "Position.h"

class E_Alpha final : public Enemy
{
public:
	E_Alpha(PositionPtr & ptr_position);

public:
	PositionPtr GetNextPosition(const PositionPtr& ptr_postion_player);

};
using AlphaPtr = std::shared_ptr<E_Alpha>;


