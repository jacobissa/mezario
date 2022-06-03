#include "Playground.h"

Playground::Playground(const int i_height , const int i_width , const int i_probability_wall , const int i_quantity_enemy)
	: mi_height(i_height)
	, mi_width(i_width)
	, mi_probability_wall(i_probability_wall)
	, mi_quantity_enemy(i_quantity_enemy)
{
	mptr_player = std::make_shared<Player>(Position(0 , 3));
	m_position_exit = Position(i_width - 1 , i_height - 4);
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
			std::cout << GetValue(Position(x , y));
		}
		std::cout << std::endl;
	}
}

void Playground::UpdateCreatures()
{
	Position position_neighbour = mptr_player->GetCurrentPosition().GetRandomnNeighbour();
	if ( IsInBounds(position_neighbour) && GetValue(position_neighbour) == Cell::e_cell_blank )
	{
		mptr_player->MoveTo(position_neighbour);
	}
	UpdateCreatre(mptr_player);

	for ( const EnemyPtr& ptr_enemy : mvec_enemy )
	{
		Position position_neighbour = ptr_enemy->GetCurrentPosition().GetRandomnNeighbour();
		if ( IsInBounds(position_neighbour) &&  GetValue(position_neighbour) == Cell::e_cell_blank )
		{
			ptr_enemy->MoveTo(position_neighbour);
		}
		UpdateCreatre(ptr_enemy);
	}
}

void Playground::Initialize()
{
	Position position_player = mptr_player->GetCurrentPosition();

	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			Position position_cell = Position(x , y);
			int i_probability = rand() % 100;
			if ( position_cell == position_player || position_cell == m_position_exit )
			{
				SetValue(position_cell , Cell::e_cell_blank);
			}
			else if ( x == 0 || x == mi_width - 1 || y == 0 || y == mi_height - 1 )
			{
				SetValue(position_cell , Cell::e_cell_wall);
			}
			else if ( i_probability < mi_probability_wall )
			{
				SetValue(position_cell , Cell::e_cell_wall);
			}
			else if ( i_probability > 95 && mi_quantity_enemy > 0 )
			{
				mvec_enemy.emplace_back(std::make_shared<Enemy>(position_cell));
				mi_quantity_enemy--;
			}
			else
			{
				SetValue(position_cell , Cell::e_cell_blank);
			}
		}
	}
}

void Playground::SetValue(Position position , enum Cell e_cell)
{
	if ( IsInBounds(position) )
	{
		mptr_matrix[position.y][position.x] = e_cell;
	}
}

char Playground::GetValue(Position position)
{
	if ( IsInBounds(position) )
	{
		return mptr_matrix[position.y][position.x];
	}
	std::cout << std::endl << std::endl << "Error: Invalid request to Playground::GetValue." << std::endl;
	std::cout << "Position (" << position.x << " , " << position.y << ") ist out of bounds!" << std::endl;
	std::exit(EXIT_FAILURE);
}

bool Playground::IsInBounds(Position position)
{
	return position.x >= 0 && position.x < mi_width&& position.y >= 0 && position.y < mi_height;
}

void Playground::UpdateCreatre(CreaturePtr creature)
{
	Position position_current = creature->GetCurrentPosition();
	Position position_previous = creature->GetPreviousPosition();
	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			Position position_cell = Position(x , y);
			if ( position_cell == position_current )
			{
				SetValue(position_cell , creature->GetCell());
			}
			else if ( position_cell == position_previous )
			{
				SetValue(position_cell , Cell::e_cell_blank);
			}
		}
	}
}