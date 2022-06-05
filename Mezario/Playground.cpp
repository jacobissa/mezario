#include "Playground.h"

Playground::Playground(const int i_height , const int i_width , const int i_probability_wall , const int i_quantity_enemy)
	: mi_height(i_height)
	, mi_width(i_width)
	, mi_probability_wall(i_probability_wall)
	, mi_quantity_enemy(i_quantity_enemy)
	, mptr_position_exit(std::make_shared<Position>(i_width - 1 , i_height - 4))
{
	PositionPtr ptr_position_player = std::make_shared<Position>(0 , 3);
	mptr_player = std::make_shared<Player>(ptr_position_player);
	mptr_matrix = new char* [mi_height];
	for ( int y = 0; y < mi_height; y++ )
	{
		mptr_matrix[y] = new char[mi_width];
	}
	Initialize();
}

Playground::~Playground()
{
	for ( int y = 0; y < mi_height; y++ )
	{
		delete[] mptr_matrix[y];
	}
	delete[] mptr_matrix;
}

void Playground::PlayerMove(enum Action e_action)
{
	PositionPtr ptr_position_player_next = mptr_player->GetNextPosition(e_action);
	if ( ptr_position_player_next && IsInBounds(ptr_position_player_next) && GetValue(ptr_position_player_next) == Cell::e_cell_blank)
	{
		mptr_player->MoveTo(ptr_position_player_next);
	}
}

void Playground::PlayerShot()
{
	if ( mptr_player->IsShotActive() )
	{
		SetValue(mptr_player->GetShotPreviousPosition() , Cell::e_cell_blank);
		SetValue(mptr_player->GetShotCurrentPosition() , Cell::e_cell_blank);
	}
	mptr_player->StartShot();
}

void Playground::UpdateCreatures()
{
	for ( const EnemyPtr& ptr_enemy : mvec_enemy )
	{
		UpdateEnemyMove(ptr_enemy);
		UpdateCreatre(ptr_enemy);
	}
	UpdateCreatre(mptr_player);
}

void Playground::PrintToConsole()
{
	PositionPtr ptr_position_cell = std::make_shared<Position>(0 , 0);
	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			ptr_position_cell->UpdatePosition(x , y);
			std::cout << GetValue(ptr_position_cell);
		}
		std::cout << std::endl;
	}
}

void Playground::Initialize()
{
	PositionPtr ptr_position_player = mptr_player->GetCurrentPosition();
	const int i_enemy_position = ( ( mi_height - 2 ) * ( mi_width - 2 ) ) / ( mi_quantity_enemy );
	int i_probability_enemy_position = rand() % i_enemy_position;
	int i_counter = 1;
	PositionPtr ptr_position_cell = std::make_shared<Position>(0 , 0);

	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			ptr_position_cell->UpdatePosition(x , y);

			int i_probability_wall = rand() % 100;
			if ( ptr_position_cell->Equals(ptr_position_player->GetPosition())
				|| ptr_position_cell->Equals(mptr_position_exit->GetPosition()) )
			{
				// keep the start end exit positions empty
				SetValue(ptr_position_cell , Cell::e_cell_blank);
			}
			else if ( x == 0 || x == mi_width - 1 || y == 0 || y == mi_height - 1 )
			{
				// draw the walls on bounds
				SetValue(ptr_position_cell , Cell::e_cell_wall);
			}
			else if ( i_counter % i_enemy_position == i_probability_enemy_position && mi_quantity_enemy > 0 )
			{
				// create the enemies
				PositionPtr ptr_position_enemy = std::make_shared<Position>(x , y);
				mvec_enemy.emplace_back(std::make_shared<Enemy>(ptr_position_enemy));
				SetValue(ptr_position_cell , Cell::e_cell_blank);
				mi_quantity_enemy--;
				i_counter++;
			}
			else if ( i_probability_wall < mi_probability_wall
					 && !ptr_position_player->IsClose(ptr_position_cell->GetPosition() , 3)
					 && !mptr_position_exit->IsClose(ptr_position_cell->GetPosition() , 3) )
			{
				// draw the walls inside the maze, except the area near start & exit positions
				SetValue(ptr_position_cell , Cell::e_cell_wall);
				i_counter++;
			}
			else
			{
				// fill the rest with empty char
				SetValue(ptr_position_cell , Cell::e_cell_blank);
				i_counter++;
			}
		}
	}
}

void Playground::SetValue(const PositionPtr& ptr_position , enum Cell e_cell)
{
	if ( IsInBounds(ptr_position) )
	{
		mptr_matrix[ptr_position->y][ptr_position->x] = e_cell;
	}
}

char Playground::GetValue(const PositionPtr& ptr_position)
{
	if ( IsInBounds(ptr_position) )
	{
		return mptr_matrix[ptr_position->y][ptr_position->x];
	}
	std::cout << std::endl << std::endl << "Error: Invalid request to Playground::GetValue." << std::endl;
	std::cout << "Position (" << ptr_position->x << " , " << ptr_position->y << ") ist out of bounds!" << std::endl;
	std::exit(EXIT_FAILURE);
}

bool Playground::IsInBounds(const PositionPtr& ptr_position)
{
	return ptr_position->x >= 0 && ptr_position->x < mi_width&& ptr_position->y >= 0 && ptr_position->y < mi_height;
}

void Playground::UpdateEnemyMove(const EnemyPtr& ptr_enemy)
{
	PositionPtr ptr_position_enemy_next = ptr_enemy->GetNextPosition();
	if ( ptr_position_enemy_next && IsInBounds(ptr_position_enemy_next) && GetValue(ptr_position_enemy_next) == Cell::e_cell_blank )
	{
		if ( !ptr_enemy->IsShotActive() )
		{
			ptr_enemy->StartShot();
		}
		ptr_enemy->MoveTo(ptr_position_enemy_next);
	}
}

void Playground::UpdateCreatureShot(const CreaturePtr& ptr_creature)
{
	if ( ptr_creature->IsShotActive() )
	{
		ptr_creature->UpdateShot();

		PositionPtr ptr_position_shot_current = ptr_creature->GetShotCurrentPosition();
		PositionPtr ptr_position_shot_previous = ptr_creature->GetShotPreviousPosition();

		if ( ptr_position_shot_current && IsInBounds(ptr_position_shot_current) && GetValue(ptr_position_shot_current) == Cell::e_cell_wall )
		{
			// remove shot, if faced a wall
			ptr_creature->StopShot();
			SetValue(ptr_position_shot_previous , Cell::e_cell_blank);
		}
		else if ( ptr_position_shot_current && !IsInBounds(ptr_position_shot_current) )
		{
			// remove shot, in case it goes out of bounds
			ptr_creature->StopShot();
			SetValue(ptr_position_shot_previous , Cell::e_cell_blank);
		}
	}
}

void Playground::UpdateCreatre(const CreaturePtr& ptr_creature)
{
	UpdateCreatureShot(ptr_creature);

	PositionPtr ptr_position_current = ptr_creature->GetCurrentPosition();
	PositionPtr ptr_position_previous = ptr_creature->GetPreviousPosition();
	PositionPtr ptr_position_shot_current = ptr_creature->GetShotCurrentPosition();
	PositionPtr ptr_position_shot_previous = ptr_creature->GetShotPreviousPosition();

	PositionPtr ptr_position_cell = std::make_shared<Position>(0 , 0);
	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			ptr_position_cell->UpdatePosition(x , y);

			if ( ptr_position_cell->Equals(ptr_position_current->GetPosition()) )
			{
				// new position of creature
				SetValue(ptr_position_cell , ptr_creature->GetCell());
			}
			else if ( ptr_position_cell->Equals(ptr_position_previous->GetPosition()) && GetValue(ptr_position_cell) == ptr_creature->GetCell() )
			{
				// remove old position of creature
				SetValue(ptr_position_cell , Cell::e_cell_blank);
			}
			else if ( ptr_creature->IsShotActive() && ptr_position_cell->Equals(ptr_position_shot_current->GetPosition()) )
			{
				// new position of creature's shot
				SetValue(ptr_position_cell , ptr_creature->GetCellShot());
			}
			else if ( ptr_creature->IsShotActive() && ptr_position_cell->Equals(ptr_position_shot_previous->GetPosition())
					 && GetValue(ptr_position_cell) == ptr_creature->GetCellShot() )
			{
				// remove old position of creature's shot
				SetValue(ptr_position_cell , Cell::e_cell_blank);
			}
		}
	}
}
