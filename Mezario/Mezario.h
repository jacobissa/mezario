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
	e_cell_wall = (char) 219 ,
	e_cell_obstacle = (char) 176,
	e_cell_player = (char) 2 ,
	e_cell_heart = (char) 3 ,
	e_cell_enemy_alpha = (char) 1 ,
	e_cell_enemy_beta = (char) 5,
	e_cell_enemy_gamma = (char) 4,
	e_cell_player_shot_up = (char) 30 ,
	e_cell_player_shot_down = (char) 31 ,
	e_cell_player_shot_left = (char) 17 ,
	e_cell_player_shot_right = (char) 16 ,
	e_cell_enemy_shot_up = (char) 208 ,
	e_cell_enemy_shot_down = (char) 210 ,
	e_cell_enemy_shot_left_right = (char) 240 ,
};

enum Action : int
{
	e_action_up = 119 ,
	e_action_down = 115 ,
	e_action_left = 97 ,
	e_action_right = 100 ,
	e_action_shot = 32 ,
};

enum Color : unsigned short
{
	e_color_black = 0 ,
	e_color_blue = 1 ,
	e_color_green = 2 ,
	e_color_cyan = 3 ,
	e_color_red = 4 ,
	e_color_magenta = 5 ,
	e_color_brown = 6 ,
	e_color_light_gray = 7 ,
	e_color_dark_gray = 8 ,
	e_color_light_blue = 9 ,
	e_color_light_green = 10 ,
	e_color_light_cyan = 11 ,
	e_color_light_red = 12 ,
	e_color_light_magenta = 13 ,
	e_color_yellow = 14 ,
	e_color_white = 15 ,
};
#endif // !MEZARIO_H
