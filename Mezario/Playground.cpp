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
			std::cout << GetValue(y,x);
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
			SetValue(y , x , '#');
		}
	}
}

void Playground::SetValue(int y , int x , char value)
{
	if ( IsInBounds(y , x) )
	{
		matrix[y][x] = value;
	}
}

char Playground::GetValue(int y , int x)
{
	if ( IsInBounds(y , x) )
	{
		return matrix[y][x];
	}
}

bool Playground::IsInBounds(int y , int x)
{
	return x >= 0 && x < mi_width && y >= 0 && y < mi_height;
}
