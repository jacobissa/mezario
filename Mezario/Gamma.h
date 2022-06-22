#ifndef GAMMA_H
#define GAMMA_H

#include "Player.h"
#include "Position.h"
#include "Enemy.h"

class Gamma final :
    public Enemy
{
public:
	Gamma(const PositionPtr& ptr_position);

public:
	PositionPtr GetNextPosition(const PositionPtr& ptr_position, const int i_time_counter) override;
	void StartShot(const PositionPtr& ptr_position, const int i_time_counter) override;

};
using GammaPtr = std::shared_ptr<Gamma>;

#endif