#ifndef ALPHA_H
#define ALPHA_H

#include "Enemy.h"
#include "Player.h"
#include "Position.h"

class Alpha final : public Enemy
{
public:
	Alpha(const PositionPtr& ptr_position);

public:
	PositionPtr GetNextPosition(const PositionPtr& ptr_postion_player, const int i_time_counter) override;
	void StartShot(const PositionPtr& ptr_position_player, const int i_time_counter) override;
	int get_another_position = -1;

};
using AlphaPtr = std::shared_ptr<Alpha>;

#endif // !ALPHA_H
