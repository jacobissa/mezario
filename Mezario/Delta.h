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
	const int time_for_explotion = rand() % 5;
	int timer = 0;

};
using DeltaPtr = std::shared_ptr<Delta>;
#endif DELTA_H

