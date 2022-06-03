#include "Mezario.h"
#include "Playground.h"
#include "Player.h"

void PlayGame()
{
	const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
	const CONSOLE_CURSOR_INFO cursor_info{ 1, FALSE };
	const COORD cursor_position{ 0,0 };
	SetConsoleCursorInfo(h_console , &cursor_info);

	const int i_width = 100;
	const int i_height = 25;
	Position position_player(1 , 1);
	Position position_enemy(i_width -2 , i_height - 2);
	PlayerPtr ptr_player = std::make_shared<Player>(position_player);
	EnemyPtr ptr_enemy = std::make_shared<Enemy>(position_enemy);
	PlaygroundPtr ptr_playground = std::make_shared<Playground>(i_height , i_width , ptr_player , ptr_enemy);

	for ( int y = 1; y < i_height - 1; y++ )
	{
		for ( int x = 1; x < i_width - 2; x++ )
		{
			SetConsoleCursorPosition(h_console , cursor_position);
			if ( y % 2  == 0)
			{
				ptr_player->MoveTo(position_player.GoLeft());
				ptr_enemy->MoveTo(position_enemy.GoRight());
			}
			else
			{
				ptr_player->MoveTo(position_player.GoRight());
				ptr_enemy->MoveTo(position_enemy.GoLeft());
			}
			ptr_playground->UpdateCreatures();
			ptr_playground->PrintToConsole();
		}
		ptr_player->MoveTo(position_player.GoDown());
		ptr_enemy->MoveTo(position_enemy.GoUp());
		ptr_playground->UpdateCreatures();
	}
}

int main()
{
	PlayGame();
}
