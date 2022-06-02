#include "Playground.h"

Playground::Playground(const int i_height , const int i_width)
	: mi_height(i_height)
	, mi_width(i_width)
{
	matrix = new char* [mi_height];
	for ( int y = 0; y < mi_height; y++ )
	{
		matrix[y] = new char[mi_width];
	}
	Initialize();
}

Playground::~Playground()
{
	for ( int y = 0; y < mi_height; y++ )
	{
		delete[] matrix[y];
	}
	delete[] matrix;
}

void Playground::PrintToConsole()
{
	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			std::cout << GetValue({ x, y });
		}
		std::cout << std::endl;
	}
}

void Playground::Initialize()
{
	for ( int y = 0; y < mi_height; y++ )
	{
		for ( int x = 0; x < mi_width; x++ )
		{
			if ( x == 0 || x == mi_width - 1 || y == 0 || y == mi_height - 1 )
			{
				SetValue(Position{ x, y } , Cell::e_cell_wall);
			}
			else
			{
				SetValue(Position{ x, y } , Cell::e_cell_blank);
			}
				
		}
	}
}

void Playground::SetValue(Position position , enum Cell e_cell)
{
	if ( IsInBounds(position) )
	{
		matrix[position.y][position.x] = e_cell;
	}
}

char Playground::GetValue(Position position)
{
	if ( IsInBounds(position) )
	{
		return matrix[position.y][position.x];
	}
}

bool Playground::IsInBounds(Position position)
{
	return position.x >= 0 && position.x < mi_width&& position.y >= 0 && position.y < mi_height;
}
