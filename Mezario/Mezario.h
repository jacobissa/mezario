#ifndef MEZARIO_H
#define MEZARIO_H

#include <iostream>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include "Position.h"


enum Cell : char
{
	e_cell_blank = ' ' ,
	e_cell_wall = '#' ,
	e_cell_player = '@' ,
	e_cell_enemy = '%' ,
	e_cell_player_shot = '~',
	e_cell_enemy_shot = ',' ,
};

enum Action : int
{
	e_action_up = 119 ,
	e_action_down = 115 ,
	e_action_left = 97 ,
	e_action_right = 100 ,
	e_action_shot = 32,
};
#endif // !MEZARIO_H