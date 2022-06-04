#include "Playground.h"

Playground::Playground(const int i_height , const int i_width , const int i_probability_wall , const int i_quantity_enemy)
	: mi_height(i_height)
	, mi_width(i_width)
	, mi_probability_wall(i_probability_wall)
	, mi_quantity_enemy(i_quantity_enemy)
	, mptr_position_exit(new Position(i_width - 1 , i_height - 4))
	, mptr_player(new Player(std::make_shared<Position>(0 , 3)))
{
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

void Playground::PrintToConsole()
{
	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			PositionPtr ptr_position_cell(new Position(x , y));
			std::cout << GetValue(ptr_position_cell);
		}
		std::cout << std::endl;
	}
}

void Playground::UpdateCreatures()
{
	PositionPtr ptr_position_neighbour = std::make_shared<Position>(mptr_player->GetCurrentPosition()->GetRandomnNeighbour());
	if ( IsInBounds(ptr_position_neighbour) && GetValue(ptr_position_neighbour) == Cell::e_cell_blank )
	{
		mptr_player->MoveTo(ptr_position_neighbour);
	}
	UpdateCreatre(mptr_player);

	for ( const EnemyPtr& ptr_enemy : mvec_enemy )
	{
		PositionPtr ptr_position_neighbour = std::make_shared<Position>(ptr_enemy->GetCurrentPosition()->GetRandomnNeighbour());
		if ( IsInBounds(ptr_position_neighbour) && GetValue(ptr_position_neighbour) == Cell::e_cell_blank )
		{
			ptr_enemy->MoveTo(ptr_position_neighbour);
		}
		UpdateCreatre(ptr_enemy);
	}
}

void Playground::Initialize()
{
	PositionPtr ptr_position_player = mptr_player->GetCurrentPosition();
	const int i_enemy_position = (( mi_height - 2 ) * ( mi_width - 2)) / (mi_quantity_enemy + 1);
	int i_counter = 0;
	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			PositionPtr ptr_position_cell(new Position(x , y));
			int i_probability = rand() % 100;
			if ( ptr_position_cell->Equals(ptr_position_player->GetPosition()) 
				|| ptr_position_cell->Equals(mptr_position_exit->GetPosition()) )
			{
				SetValue(ptr_position_cell , Cell::e_cell_blank);
			}
			else if ( x == 0 || x == mi_width - 1 || y == 0 || y == mi_height - 1 )
			{
				SetValue(ptr_position_cell , Cell::e_cell_wall);
			}
			else if ( i_counter % i_enemy_position == 0 && i_counter != i_enemy_position && mi_quantity_enemy > 0 )
			{
				mvec_enemy.emplace_back(std::make_shared<Enemy>(ptr_position_cell));
				SetValue(ptr_position_cell , Cell::e_cell_blank);
				mi_quantity_enemy--;
				i_counter++;
			}
			else if ( i_probability < mi_probability_wall
					 && !ptr_position_player->IsClose(ptr_position_cell->GetPosition(), 3)
					 && !mptr_position_exit->IsClose(ptr_position_cell->GetPosition(), 3) )
			{
				SetValue(ptr_position_cell , Cell::e_cell_wall);
				i_counter++;
			}
			else
			{
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

void Playground::UpdateCreatre(CreaturePtr creature)
{
	PositionPtr ptr_position_current = creature->GetCurrentPosition();
	PositionPtr ptr_position_previous = creature->GetPreviousPosition();
	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			PositionPtr ptr_position_cell(new Position(x , y));

			if ( ptr_position_cell->Equals(ptr_position_current->GetPosition()) )
			{
				SetValue(ptr_position_cell , creature->GetCell());
			}
			else if ( ptr_position_cell->Equals(ptr_position_previous->GetPosition()) )
			{
				SetValue(ptr_position_cell , Cell::e_cell_blank);
			}
		}
	}
}