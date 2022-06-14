#ifndef CREATURE_H
#define CREATURE_H

#include <memory>

#include "Mezario.h"
#include "Position.h"


struct CellShot
{
	Cell e_cell_shot_up;
	Cell e_cell_shot_down;
	Cell e_cell_shot_left;
	Cell e_cell_shot_right;
};

class Creature
{
public:
	Creature(const PositionPtr& ptr_position , const Cell e_cell_creature , const CellShot s_cell_shot);

public:
	Cell GetCellCreature() const;
	Cell GetCellShot() const;
	const PositionPtr& GetCurrentPosition();
	const PositionPtr& GetPreviousPosition();
	const PositionPtr& GetShotCurrentPosition();
	const PositionPtr& GetShotPreviousPosition();
	void MoveTo(const PositionPtr& ptr_position);
	bool IsShotActive() const;
	void StopShot();
	void UpdateShot();

protected:
	Cell me_cell_creature = Cell::e_cell_blank;
	CellShot ms_cell_shot;
	PositionPtr mptr_position_current;
	PositionPtr mptr_position_previous;
	PositionPtr mptr_position_shot_current;
	PositionPtr mptr_position_shot_previous;
	bool mb_is_shot_active = false;


};
using CreaturePtr = std::shared_ptr<Creature>;

#endif // !CREATURE_H