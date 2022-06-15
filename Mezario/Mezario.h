#ifndef MEZARIO_H
#define MEZARIO_H

enum Cell : char
{
	e_cell_blank = ' ' ,
	e_cell_wall = static_cast<char>( 219 ) ,
	e_cell_obstacle = static_cast<char>( 176 ) ,
	e_cell_player = static_cast<char>( 2 ) ,
	e_cell_heart = static_cast<char>( 3 ) ,
	e_cell_enemy_alpha = static_cast<char>( 1 ) ,
	e_cell_enemy_beta = static_cast<char>( 15 ) ,
	e_cell_enemy_gamma = static_cast<char>( 184 ) ,
	e_cell_player_shot_up = static_cast<char>( 30 ) ,
	e_cell_player_shot_down = static_cast<char>( 31 ) ,
	e_cell_player_shot_left = static_cast<char>( 17 ) ,
	e_cell_player_shot_right = static_cast<char>( 16 ) ,
	e_cell_enemy_shot_alpha = static_cast<char>( 42 ) ,

};

enum Action : int
{
	e_action_up = 119 ,		// W
	e_action_down = 115 ,	// S
	e_action_left = 97 ,	// A
	e_action_right = 100 ,	// D
	e_action_shot = 32 ,	// Space bar
	e_action_yes = 121 ,	// Y
	e_action_no = 110 ,		// N
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
