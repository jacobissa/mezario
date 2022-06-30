#ifndef DELTA_H
#define DELTA_H

#include "Enemy.h"
#include "Player.h"
#include "Position.h"

class Delta : public Enemy
{
public:
	Delta(const PositionPtr& ptr_position);

public:
	PositionPtr GetNextPosition(const PositionPtr& ptr_postion_player, const int i_time_counter) override;
	void StartShot(const PositionPtr& ptr_position_player, const int i_time_counter) override;
	int time_for_explotion = -1;
	int timer = -1;
	bool explosed = false;

};
using DeltaPtr = std::shared_ptr<Delta>;
#endif DELTA_H

