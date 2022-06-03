#include "Playground.h"

Playground::Playground(const int i_height , const int i_width , Player* ptr_player)
	: mi_height(i_height)
	, mi_width(i_width)
	, mptr_player(ptr_player)
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
	UpdatePlayer();
	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			std::cout << GetValue(Position(x , y));
		}
		std::cout << std::endl;
	}
}

void Playground::UpdatePlayer()
{
	Position position_player_current = mptr_player->GetCurrentPosition();
	Position position_player_previous = mptr_player->GetPreviousPosition();
	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			Position position_cell = Position(x , y);
			if ( position_cell == position_player_current )
			{
				SetValue(position_cell , Cell::e_cell_player);
			}
			else if ( position_cell == position_player_previous )
			{
				SetValue(position_cell , Cell::e_cell_blank);
			}
		}
	}
}

void Playground::Initialize()
{
	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			Position position_cell = Position(x , y);

			if ( x == 0 || x == mi_width - 1 || y == 0 || y == mi_height - 1 )
			{
				SetValue(position_cell , Cell::e_cell_wall);
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
