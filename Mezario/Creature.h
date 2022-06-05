#ifndef CREATURE_H
#define CREATURE_H

#include "Mezario.h"

class Creature
{
public:
	Creature(PositionPtr& ptr_position);

public:
	enum Cell GetCell();
	enum Cell GetCellShot();
	const PositionPtr& GetCurrentPosition();
	const PositionPtr& GetPreviousPosition();
	const PositionPtr& GetShotCurrentPosition();
	const PositionPtr& GetShotPreviousPosition();
	void MoveTo(PositionPtr& ptr_position);
	void StartShot();
	bool IsShotActive();
	void StopShot();
	void UpdateShot();

protected:
	enum Cell me_cell = Cell::e_cell_blank;
	enum Cell me_cell_shot = Cell::e_cell_blank;
	PositionPtr mptr_position_current;
	PositionPtr mptr_position_previous;
	PositionPtr mptr_position_shot_current;
	PositionPtr mptr_position_shot_previous;
	bool mb_is_shot_active = false;

};
using CreaturePtr = std::shared_ptr<Creature>;

#endif // !CREATURE_H