#ifndef MEZARIO_H
#define MEZARIO_H

#include <iostream>
#include <Windows.h>
#include <vector>
#include "Position.h"


enum Cell : char
{
	e_cell_blank = ' ' ,
	e_cell_wall = '#' ,
	e_cell_player = '@' ,
	e_cell_enemy = '%' ,
};

#endif // !MEZARIO_H