#include "Creature.h"

Creature::Creature(PositionPtr& ptr_position, enum Cell e_cell_creature, const CellShot s_cell_shot)
	: mptr_position_current(ptr_position)
	, mptr_position_previous(ptr_position)
	, ms_cell_shot(s_cell_shot)
	, me_cell_creature(e_cell_creature)
{
}

Cell Creature::GetCellCreature()
{
	return me_cell_creature;
}

Cell Creature::GetCellShot()
{
	if ( mb_is_shot_active )
	{
		if ( mptr_position_shot_current->Equals(mptr_position_shot_previous->GetUpPosition()) )
		{
			return ms_cell_shot.e_cell_shot_up;
		}
		else if ( mptr_position_shot_current->Equals(mptr_position_shot_previous->GetDownPosition()) )
		{
			return ms_cell_shot.e_cell_shot_down;
		}
		else if ( mptr_position_shot_current->Equals(mptr_position_shot_previous->GetLeftPosition()) )
		{
			return ms_cell_shot.e_cell_shot_left;
		}
		else if ( mptr_position_shot_current->Equals(mptr_position_shot_previous->GetRightPosition()) )
		{
			return ms_cell_shot.e_cell_shot_right;
		}
	}
	std::cout << std::endl << std::endl << "Error: Invalid request to Creature::GetCellShot." << std::endl;
	std::cout << "Make sure the shot is active, before calling this function!" << std::endl;
	std::exit(EXIT_FAILURE);
}

const PositionPtr& Creature::GetCurrentPosition()
{
	return mptr_position_current;
}

const PositionPtr& Creature::GetPreviousPosition()
{
	return mptr_position_previous;
}

const PositionPtr& Creature::GetShotCurrentPosition()
{
	return mptr_position_shot_current;
}

const PositionPtr& Creature::GetShotPreviousPosition()
{
	return mptr_position_shot_previous;
}

void Creature::MoveTo(PositionPtr& ptr_position)
{
	mptr_position_previous = mptr_position_current;
	mptr_position_current = ptr_position;
}

void Creature::StartShot()
{
	if ( mptr_position_current->Equals(mptr_position_previous->GetPosition()))
	{
		mb_is_shot_active = false;
		// creatre, who didn't move yet, can't start shooting

	}
	else
	{
		mb_is_shot_active = true;
		mptr_position_shot_current = std::make_shared<Position>(mptr_position_current->GetPosition());
		mptr_position_shot_previous = std::make_shared<Position>(mptr_position_previous->GetPosition());
		
		
	}
}

bool Creature::IsShotActive()
{
	return mb_is_shot_active;
}

void Creature::StopShot()
{
	mb_is_shot_active = false;
	mptr_position_shot_current = nullptr;
	mptr_position_shot_previous = nullptr;
}
void Creature::UpdateShot()
{
	if ( mb_is_shot_active )
	{
		if ( mptr_position_shot_current->Equals(mptr_position_shot_previous->GetUpPosition()) )
		{
			mptr_position_shot_previous = mptr_position_shot_current;
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_shot_current->GetUpPosition());
		}
		else if ( mptr_position_shot_current->Equals(mptr_position_shot_previous->GetDownPosition()) )
		{
			mptr_position_shot_previous = mptr_position_shot_current;
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_shot_current->GetDownPosition());
		}
		else if ( mptr_position_shot_current->Equals(mptr_position_shot_previous->GetRightPosition()) )
		{
			mptr_position_shot_previous = mptr_position_shot_current;
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_shot_current->GetRightPosition());
		}
		else if ( mptr_position_shot_current->Equals(mptr_position_shot_previous->GetLeftPosition()) )
		{
			mptr_position_shot_previous = mptr_position_shot_current;
			mptr_position_shot_current = std::make_shared<Position>(mptr_position_shot_current->GetLeftPosition());
		}

	}
}
bool Creature::IsAlive()
{
	return this->alive;
}
