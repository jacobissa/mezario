#pragma once
#include <iostream>

struct Position
{
	int x;
	int y;
};

enum Cell : char
{
	Blank = ' ' ,
	Wall = '#' ,
};