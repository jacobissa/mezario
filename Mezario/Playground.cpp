#include "Playground.h"

#include <cassert>
#include <iostream>

#include "Alpha.h"

Playground::Playground(const int i_height , const int i_width , const int i_hearts , const int i_probability_wall , const int i_quantity_enemy , const int i_time_max)
	: mi_height(i_height)
	, mi_width(i_width)
	, mi_hearts(i_hearts)
	, mi_probability_wall(i_probability_wall)
	, mi_quantity_enemy(i_quantity_enemy)
	, mi_time_max(i_time_max)
	, mptr_position_exit(std::make_shared<Position>(i_width - 1 , i_height - 4))
{
	mi_coins = 0;
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

void Playground::PlayerMove(const Action e_action)
{
	if ( mtime_start.time_since_epoch().count() == 0 )
	{
		mtime_start = std::chrono::steady_clock::now();
	}
	const PositionPtr ptr_position_player_next = mptr_player->GetNextPosition(e_action);
	if ( ptr_position_player_next && IsInBounds(ptr_position_player_next) )
	{
		if ( GetValue(ptr_position_player_next) == Cell::e_cell_blank )
		{
			mptr_player->MoveTo(ptr_position_player_next);
		}
		else if ( GetValue(ptr_position_player_next) == Cell::e_cell_heart )
		{
			mi_hearts++;
			mptr_player->MoveTo(ptr_position_player_next);
		}
		else if ( GetValue(ptr_position_player_next) == Cell::e_cell_coin )
		{
			mi_coins++;
			mptr_player->MoveTo(ptr_position_player_next);
		}
	}
}

void Playground::PlayerShot() const
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
	UpdatePlayerShot();
	UpdateCreature(mptr_player);
	for ( const EnemyPtr& ptr_enemy : mvec_enemy )
	{
		UpdateEnemyMove(ptr_enemy);
		UpdateEnemyShot(ptr_enemy);
		UpdateCreature(ptr_enemy);
	}
}

void Playground::PrintToConsole(const HANDLE& h_console) const
{
	const PositionPtr ptr_position_cell = std::make_shared<Position>(0 , 0);
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

int Playground::GetTimeLeft() const
{
	return mi_time_max - GetTimeCounter();
}

int Playground::GetHearts() const
{
	return mi_hearts;
}

int Playground::GetCoins() const
{
	return mi_coins;
}

int Playground::GetEnemies() const
{
	return static_cast<int>( mvec_enemy.size() );
}

bool Playground::IsWin() const
{
	return mptr_player->GetCurrentPosition()->Equals(mptr_position_exit->GetPosition());
}

bool Playground::IsLose() const
{
	return mi_hearts == 0 || GetTimeCounter() >= mi_time_max;
}

void Playground::Initialize()
{
	const PositionPtr ptr_position_player = mptr_player->GetCurrentPosition();
	const int i_enemy_position = ( ( mi_height - 2 ) * ( mi_width - 2 ) ) / ( mi_quantity_enemy );
	const int i_probability_enemy_position = rand() % i_enemy_position;
	int i_counter = 1;
	const PositionPtr ptr_position_cell = std::make_shared<Position>(0 , 0);

	for ( int y = 0; y < mi_height; y++ )
	{
		const int i_heart_position_x = rand() % mi_width;

		for ( int x = 0; x < mi_width; x++ )
		{
			ptr_position_cell->UpdatePosition(x , y);

			const int i_probability_wall = rand() % 100;
			if ( ptr_position_cell->Equals(ptr_position_player->GetPosition())
				|| ptr_position_cell->Equals(mptr_position_exit->GetPosition()) )
			{
				// keep the start end exit positions empty
				SetValue(ptr_position_cell , Cell::e_cell_blank);
			}
			else if ( x == 0 || x == mi_width - 1 || y == 0 || y == mi_height - 1 )
			{
				// draw the bounds on bounds
				SetValue(ptr_position_cell , Cell::e_cell_bound);
			}
			else if ( i_counter % i_enemy_position == i_probability_enemy_position && mi_quantity_enemy > 0 )
			{
				// create the enemies
				PositionPtr ptr_position_enemy = std::make_shared<Position>(x , y);
				EnemyPtr ptr_enemy;
				switch ( rand() % 4 )
				{
					case 0:
						{
							ptr_enemy = std::make_shared<Alpha>(ptr_position_enemy);
						}
						break;
					case 1:
						{
							ptr_enemy = std::make_shared<Beta>(ptr_position_enemy);
						}
						break;
					case 2:
						{
							ptr_enemy = std::make_shared<Gamma>(ptr_position_enemy);
						}
						break;
					case 3:
						{
							ptr_enemy = std::make_shared<Delta>(ptr_position_enemy);
						}
						break;
				}
				mvec_enemy.emplace_back(ptr_enemy);
				SetValue(ptr_position_cell , Cell::e_cell_blank);
				mi_quantity_enemy--;
				i_counter++;
			}
			else if ( x == i_heart_position_x )
			{
				SetValue(ptr_position_cell , Cell::e_cell_heart);
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
			else if ( i_probability_wall < ( mi_probability_wall * 1.5 )
					 && !ptr_position_player->IsClose(ptr_position_cell->GetPosition() , 3)
					 && !mptr_position_exit->IsClose(ptr_position_cell->GetPosition() , 3) )
			{
				// draw the obstacles inside the maze, except the area near start & exit positions
				SetValue(ptr_position_cell , Cell::e_cell_obstacle);
				i_counter++;
			}
			else if ( i_probability_wall < ( mi_probability_wall * 2 ) )
			{
				// draw the coins
				SetValue(ptr_position_cell , Cell::e_cell_coin);
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

void Playground::SetValue(const PositionPtr& ptr_position , const Cell e_cell) const
{
	if ( IsInBounds(ptr_position) )
	{
		mptr_matrix[ptr_position->y][ptr_position->x] = e_cell;
	}
}

char Playground::GetValue(const PositionPtr& ptr_position) const
{
	if ( IsInBounds(ptr_position) )
	{
		return mptr_matrix[ptr_position->y][ptr_position->x];
	}
	assert(!"Error: Invalid request to Playground::GetValue. Position is out of bounds!");
	return {};
}

bool Playground::IsInBounds(const PositionPtr& ptr_position) const
{
	return ptr_position->x >= 0 && ptr_position->x < mi_width&& ptr_position->y >= 0 && ptr_position->y < mi_height;
}

void Playground::UpdateEnemyMove(const EnemyPtr& ptr_enemy) const
{

	const PositionPtr ptr_position_enemy_next = ptr_enemy->GetNextPosition(mptr_player->GetCurrentPosition() , GetTimeCounter());
	if ( ptr_position_enemy_next && !ptr_enemy->IsShotActive() && IsInBounds(ptr_position_enemy_next) )
	{
		// Move the enemy, only when it has no active shot.
		if ( GetValue(ptr_position_enemy_next) == Cell::e_cell_blank || GetValue(ptr_position_enemy_next) == Cell::e_cell_heart || GetValue(ptr_position_enemy_next) == Cell::e_cell_coin )
		{
			ptr_enemy->MoveTo(ptr_position_enemy_next);
		}
		else if ( const auto& ptr_alpha = std::dynamic_pointer_cast<Alpha>(ptr_enemy) )
		{
			// try to move in other position when the next position is wall.
			ptr_alpha->get_another_position ++;
		}
	}
}

void Playground::UpdateEnemyShot(const EnemyPtr& ptr_enemy)
{

	if ( !ptr_enemy->IsShotActive() )
	{
		ptr_enemy->StartShot(mptr_player->GetCurrentPosition() , GetTimeCounter());
	}
	else
	{
		if ( const auto& ptr_delta = std::dynamic_pointer_cast<Delta>(ptr_enemy) )
		{
			if ( !ptr_delta->explosed )
			{
				std::vector<PositionPtr> ptr_position_shot_all = ptr_delta->GetAllAroundPosition();
				for ( PositionPtr var : ptr_position_shot_all )
				{
					if ( GetValue(var) == Cell::e_cell_wall )
					{
						SetValue(var, Cell::e_cell_obstacle);
					}
					else if ( GetValue(var) == Cell::e_cell_player )
					{
						mi_hearts = 0;
					}
					else if ( GetValue(var) != Cell::e_cell_bound )
					{
						SetValue(var, Cell::e_cell_enemy_shot_delta);
					}
				}
				SetValue(ptr_enemy->GetCurrentPosition(), Cell::e_cell_blank);
				ptr_delta->explosed = true;
			}
		}
		else
		{
		ptr_enemy->UpdateShot();

		const PositionPtr ptr_position_shot_current = ptr_enemy->GetShotCurrentPosition();
		const PositionPtr ptr_position_shot_previous = ptr_enemy->GetShotPreviousPosition();

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
				switch ( ptr_enemy->GetEnemyType() )
				{
					case Cell::e_cell_enemy_alpha : 
					case Cell::e_cell_enemy_beta :
						{
							mi_hearts--;
						}
						break;
					case Cell::e_cell_enemy_gamma:
						{
							mi_hearts -= 2;
						}
						break;
				}
				SetValue(ptr_position_shot_previous , Cell::e_cell_blank);
				SetValue(ptr_position_shot_current , Cell::e_cell_blank);
				ptr_enemy->StopShot();
				
			}
			else if ( mptr_player->IsShotActive() && ptr_position_shot_current->Equals(mptr_player->GetShotCurrentPosition()->GetPosition()) )
			{
				if ( ptr_enemy->GetEnemyType() == Cell::e_cell_enemy_gamma )
				{
					SetValue(ptr_position_shot_current, Cell::e_cell_obstacle);
				}
				// Enemy's shot faces the player's shot --> delete both shots
				ptr_enemy->StopShot();
				mptr_player->StopShot();
			}
			else
			{
				switch ( GetValue(ptr_position_shot_current) )
				{
					case Cell::e_cell_bound:
					case Cell::e_cell_wall:
					case Cell::e_cell_enemy_alpha:
					case Cell::e_cell_enemy_beta:
					case Cell::e_cell_enemy_gamma:
					case Cell::e_cell_enemy_delta:
					case Cell::e_cell_enemy_shot_alpha:
					case Cell::e_cell_enemy_shot_beta:
					case Cell::e_cell_enemy_shot_gamma:
					case Cell::e_cell_enemy_shot_delta:
						{
							// remove shot, if faced a wall or another enemy, or another enemy's shot
							ptr_enemy->StopShot();
						}
						break;
					case Cell::e_cell_obstacle:
					case Cell::e_cell_heart:
					case Cell::e_cell_coin:
						{
							if ( ptr_enemy->GetEnemyType() == Cell::e_cell_enemy_gamma )
							{
								SetValue(ptr_position_shot_current, Cell::e_cell_obstacle);
							}
							else
							{
								SetValue(ptr_position_shot_current, Cell::e_cell_blank);
							}
							ptr_enemy->StopShot();
						}
						break;
					default:
						break;
				}
			}
			SetValue(ptr_position_shot_previous , Cell::e_cell_blank);
		}
		}
	}
}

void Playground::UpdatePlayerShot()
{
	if ( mptr_player->IsShotActive() )
	{
		mptr_player->UpdateShot();

		const PositionPtr ptr_position_shot_current = mptr_player->GetShotCurrentPosition();
		const PositionPtr ptr_position_shot_previous = mptr_player->GetShotPreviousPosition();

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
					case Cell::e_cell_bound:
					case Cell::e_cell_wall:
						{
							// remove shot, if faced a wall
							mptr_player->StopShot();
						}
						break;
					case Cell::e_cell_enemy_alpha:
					case Cell::e_cell_enemy_beta:
					case Cell::e_cell_enemy_gamma:
					case Cell::e_cell_enemy_delta:
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
					case Cell::e_cell_enemy_shot_alpha:
					case Cell::e_cell_enemy_shot_beta:
					case Cell::e_cell_enemy_shot_gamma:
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
					case Cell::e_cell_obstacle:
					case Cell::e_cell_heart:
					case Cell::e_cell_enemy_shot_delta:
						{
							SetValue(ptr_position_shot_current , Cell::e_cell_blank);
							mptr_player->StopShot();
						}
						break;
					default:;
				}
			}
			SetValue(ptr_position_shot_previous , Cell::e_cell_blank);
		}
	}
}

void Playground::UpdateCreature(const CreaturePtr& ptr_creature) const
{
	const PositionPtr ptr_position_current = ptr_creature->GetCurrentPosition();
	const PositionPtr ptr_position_previous = ptr_creature->GetPreviousPosition();
	const PositionPtr ptr_position_shot_current = ptr_creature->GetShotCurrentPosition();
	const PositionPtr ptr_position_shot_previous = ptr_creature->GetShotPreviousPosition();

	const PositionPtr ptr_position_cell = std::make_shared<Position>(0 , 0);
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


void Playground::PrintCell(const HANDLE& h_console , const Cell e_cell)
{
	switch ( e_cell )
	{
		case Cell::e_cell_blank:
			{
				SetConsoleTextAttribute(h_console , Color::e_color_black);
				std::cout << e_cell;
			}
			break;
		case Cell::e_cell_bound:
		case Cell::e_cell_wall:
			{
				SetConsoleTextAttribute(h_console , Color::e_color_brown);
				std::cout << e_cell;
			}
			break;
		case Cell::e_cell_obstacle:
			{
				SetConsoleTextAttribute(h_console , Color::e_color_white);
				std::cout << e_cell;
			}
			break;
		case Cell::e_cell_heart:
			{
				SetConsoleTextAttribute(h_console , Color::e_color_cyan);
				std::cout << e_cell;
			}
			break;
		case Cell::e_cell_coin:
			{
				SetConsoleTextAttribute(h_console , Color::e_color_light_cyan);
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
		case Cell::e_cell_enemy_beta:
		case Cell::e_cell_enemy_gamma:
		case Cell::e_cell_enemy_delta:
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
		case Cell::e_cell_enemy_shot_alpha:
		case Cell::e_cell_enemy_shot_beta:
		case Cell::e_cell_enemy_shot_gamma:
		case Cell::e_cell_enemy_shot_delta:

			{
				SetConsoleTextAttribute(h_console , Color::e_color_light_red);
				std::cout << e_cell;
			}
			break;
		default:
			break;
	}
}


int Playground::GetTimeCounter() const
{
	if ( mtime_start.time_since_epoch().count() == 0 )
	{
		return 0;
	}
	const auto time_current = std::chrono::steady_clock::now();
	const std::chrono::seconds duration_time = std::chrono::duration_cast<std::chrono::seconds>( time_current - mtime_start );
	return static_cast<int>( duration_time.count() );
}

