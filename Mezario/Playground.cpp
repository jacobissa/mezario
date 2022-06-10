#include "Playground.h"
#include "Alpha.h"

Playground::Playground(const int i_height , const int i_width , const int i_hearts , const int i_probability_wall , const int i_quantity_enemy)
	: mi_height(i_height)
	, mi_width(i_width)
	, mi_hearts(i_hearts)
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
	if ( ptr_position_player_next && IsInBounds(ptr_position_player_next) && GetValue(ptr_position_player_next) == Cell::e_cell_blank )
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
		UpdateEnemyShot(ptr_enemy);
		UpdateCreatre(ptr_enemy);
	}
	UpdatePlayerShot();
	UpdateCreatre(mptr_player);
}

void Playground::PrintToConsole(const HANDLE& h_console)
{
	PositionPtr ptr_position_cell = std::make_shared<Position>(0 , 0);
	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			ptr_position_cell->UpdatePosition(x , y);
			PrintCell(h_console , static_cast<enum Cell>( GetValue(ptr_position_cell) ));
		}
		std::cout << std::endl;
	}
}

int Playground::GetHearts()
{
	return mi_hearts;
}

bool Playground::IsWin()
{
	return mptr_player->GetCurrentPosition()->Equals(mptr_position_exit->GetPosition());
}

bool Playground::IsLose()
{
	return mi_hearts == 0;
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
				AlphaPtr ptr_enemy = std::make_shared<Alpha>(ptr_position_enemy);
				mvec_enemy.emplace_back(ptr_enemy);
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

	PositionPtr ptr_position_enemy_next = ptr_enemy->GetNextPosition(mptr_player->GetCurrentPosition());
	if ( ptr_position_enemy_next && !ptr_enemy->IsShotActive() && IsInBounds(ptr_position_enemy_next) && GetValue(ptr_position_enemy_next) == Cell::e_cell_blank )
	{
		// Move the enemy, only when it has no active shot.
		ptr_enemy->MoveTo(ptr_position_enemy_next);
	}
}

void Playground::UpdateEnemyShot(const EnemyPtr& ptr_enemy)
{

	if ( !ptr_enemy->IsShotActive() )
	{
		ptr_enemy->StartShot(mptr_player->GetCurrentPosition());
	}
	else
	{
		ptr_enemy->UpdateShot();

		PositionPtr ptr_position_shot_current = ptr_enemy->GetShotCurrentPosition();
		PositionPtr ptr_position_shot_previous = ptr_enemy->GetShotPreviousPosition();

		if ( ptr_position_shot_current && ptr_position_shot_previous )
		{
			if ( !IsInBounds(ptr_position_shot_current) )
			{
				// remove shot, in case it goes out of bounds
				ptr_enemy->StopShot();
			}
			else if ( ptr_position_shot_current->Equals(mptr_player->GetCurrentPosition()->GetPosition()) )
			{
				// enemy's shot touched the player
				ptr_enemy->StopShot();
				mi_hearts--;
			}
			else if ( mptr_player->IsShotActive() && ptr_position_shot_current->Equals(mptr_player->GetShotCurrentPosition()->GetPosition()) )
			{
				// Enemy's shot faces the player's shot --> delete both shots
				ptr_enemy->StopShot();
				mptr_player->StopShot();
			}
			else
			{
				switch ( GetValue(ptr_position_shot_current) )
				{
					case Cell::e_cell_wall:
					case Cell::e_cell_enemy_alpha:
					case Cell::e_cell_enemy_shot_up:
					case Cell::e_cell_enemy_shot_down:
					case Cell::e_cell_enemy_shot_left_right:
						{
							// remove shot, if faced a wall or another enemy, or another enemy's shot
							ptr_enemy->StopShot();
						}
						break;
				}
			}
			SetValue(ptr_position_shot_previous , Cell::e_cell_blank);
		}
		if ( ptr_position_shot_current && IsInBounds(ptr_position_shot_current) && GetValue(ptr_position_shot_current) == Cell::e_cell_wall )
		{
			// remove shot, if faced a wall
			ptr_enemy->StopShot();
			SetValue(ptr_position_shot_previous , Cell::e_cell_blank);
		}
	}
}

void Playground::UpdatePlayerShot()
{
	if ( mptr_player->IsShotActive() )
	{
		mptr_player->UpdateShot();

		PositionPtr ptr_position_shot_current = mptr_player->GetShotCurrentPosition();
		PositionPtr ptr_position_shot_previous = mptr_player->GetShotPreviousPosition();

		if ( ptr_position_shot_current && ptr_position_shot_previous )
		{
			if ( !IsInBounds(ptr_position_shot_current) )
			{
				// remove shot, in case it goes out of bounds
				mptr_player->StopShot();
			}
			else
			{
				switch ( GetValue(ptr_position_shot_current) )
				{
					case Cell::e_cell_wall:
						{
							// remove shot, if faced a wall
							mptr_player->StopShot();
						}
						break;
					case Cell::e_cell_enemy_alpha:
						{
							// Player's Shot kills an enemy
							mvec_enemy.erase(
								std::remove_if(mvec_enemy.begin() , mvec_enemy.end() ,
											   [&] (const EnemyPtr& ptr_enemy)
							{
								if ( ptr_enemy->GetCurrentPosition()->Equals(ptr_position_shot_current->GetPosition()) )
								{
									SetValue(ptr_enemy->GetCurrentPosition() , Cell::e_cell_blank);
									if ( ptr_enemy->IsShotActive() )
									{
										SetValue(ptr_enemy->GetShotCurrentPosition() , Cell::e_cell_blank);
										ptr_enemy->StopShot();
									}
									return true;
								}
								else
								{
									return false;
								}
							}) ,
								mvec_enemy.end());
							mptr_player->StopShot();
						}
						break;
					case Cell::e_cell_enemy_shot_up:
					case Cell::e_cell_enemy_shot_down:
					case Cell::e_cell_enemy_shot_left_right:
						{
							// Player's shot faces an enemy's shot --> delete both shots
							for ( const EnemyPtr& ptr_enemy : mvec_enemy )
							{
								if ( ptr_enemy->IsShotActive() && ptr_enemy->GetShotCurrentPosition()->Equals(ptr_position_shot_current->GetPosition()) )
								{
									SetValue(ptr_enemy->GetShotCurrentPosition() , Cell::e_cell_blank);
									ptr_enemy->StopShot();
								}
							}
							mptr_player->StopShot();
						}
						break;
				}
			}
			SetValue(ptr_position_shot_previous , Cell::e_cell_blank);
		}
	}
}

void Playground::UpdateCreatre(const CreaturePtr& ptr_creature)
{
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
				SetValue(ptr_position_cell , ptr_creature->GetCellCreature());
			}
			else if ( ptr_position_cell->Equals(ptr_position_previous->GetPosition()) && GetValue(ptr_position_cell) == ptr_creature->GetCellCreature() )
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




void Playground::PrintCell(const HANDLE& h_console , enum Cell e_cell)
{
	switch ( e_cell )
	{
		case Cell::e_cell_blank:
			{
				SetConsoleTextAttribute(h_console , Color::e_color_black);
				std::cout << e_cell;
			}
			break;
		case Cell::e_cell_wall:
			{
				SetConsoleTextAttribute(h_console , Color::e_color_brown);
				std::cout << e_cell;
			}
			break;
		case Cell::e_cell_player:
			{
				SetConsoleTextAttribute(h_console , Color::e_color_green);
				std::cout << e_cell;
			}
			break;
		case Cell::e_cell_enemy_alpha:
			{
				SetConsoleTextAttribute(h_console , Color::e_color_red);
				std::cout << e_cell;
			}
			break;
		case Cell::e_cell_player_shot_up:
		case Cell::e_cell_player_shot_down:
		case Cell::e_cell_player_shot_left:
		case Cell::e_cell_player_shot_right:
			{
				SetConsoleTextAttribute(h_console , Color::e_color_light_green);
				std::cout << e_cell;
			}
			break;
		case Cell::e_cell_enemy_shot_up:
		case Cell::e_cell_enemy_shot_down:
		case Cell::e_cell_enemy_shot_left_right:
			{
				SetConsoleTextAttribute(h_console , Color::e_color_light_red);
				std::cout << e_cell;
			}
			break;
		default:
			break;
	}
}
