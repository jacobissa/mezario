#ifndef CREATURE_H
#define CREATURE_H

#include "Mezario.h"


struct CellShot
{
	enum Cell e_cell_shot_up;
	enum Cell e_cell_shot_down;
	enum Cell e_cell_shot_left;
	enum Cell e_cell_shot_right;
};

struct CellCreature
{
	enum Cell e_cell_player;
	enum Cell e_cell_enemy_alpha;
	enum Cell e_cell_enemy_beta;
	enum Cell e_cell_enemy_gamma;
};

class Creature
{
public:
	Creature(PositionPtr& ptr_position, enum Cell e_cell_creature, const CellShot s_cell_shot);

public:
	enum Cell GetCellCreature();
	enum Cell GetCellShot();
	const PositionPtr& GetCurrentPosition();
	const PositionPtr& GetPreviousPosition();
	const PositionPtr& GetShotCurrentPosition();
	const PositionPtr& GetShotPreviousPosition();
	void MoveTo(PositionPtr& ptr_position);
	void StartShot(const PositionPtr& ptr_postion_player);
	bool IsShotActive();
	void StopShot();
	void UpdateShot();
	bool IsAlive();

protected:
	enum Cell me_cell_creature = Cell::e_cell_blank;
	CellShot ms_cell_shot;
	PositionPtr mptr_position_current;
	PositionPtr mptr_position_previous;
	PositionPtr mptr_position_shot_current;
	PositionPtr mptr_position_shot_previous;
	bool mb_is_shot_active = false;
	bool alive = true;

};
using CreaturePtr = std::shared_ptr<Creature>;

#endif // !CREATURE_H