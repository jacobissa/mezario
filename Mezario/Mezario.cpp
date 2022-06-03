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
	PlayerPtr ptr_player = std::make_shared<Player>(Position(1 , 1));
	EnemyPtr ptr_enemy = std::make_shared<Enemy>(Position(98 , 23));
	PlaygroundPtr ptr_playground = std::make_shared<Playground>(i_height , i_width , ptr_player , ptr_enemy);

	for ( int y = 1; y < i_height - 1; y++ )
	{
		for ( int x = 1; x < i_width - 1; x++ )
		{
			SetConsoleCursorPosition(h_console , cursor_position);
			ptr_player->MoveTo(Position(x , y));
			ptr_enemy->MoveTo(Position(i_width - x - 1 , i_height - y - 1));
			ptr_playground->PrintToConsole();
		}
	}
}

int main()
{
	PlayGame();
}
