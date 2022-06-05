#include "Mezario.h"
#include "Playground.h"
#include "Player.h"

void PlayGame()
{
	const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
	const CONSOLE_CURSOR_INFO cursor_info{ 1, FALSE };
	const COORD cursor_position{ 0,0 };
	SetConsoleCursorInfo(h_console , &cursor_info);
	srand(static_cast<unsigned int>( time(NULL) ));

	const int i_width = 100;
	const int i_height = 25;

	PlaygroundPtr ptr_playground = std::make_shared<Playground>(i_height , i_width , 15 , 15);

	while ( true )
	{
		SetConsoleCursorPosition(h_console , cursor_position);
		while ( _kbhit() )
		{
			const int int_action = _getch();
			switch ( int_action )
			{
				case e_action_up:
				case e_action_down:
				case e_action_left:
				case e_action_right:
					{
						ptr_playground->PlayerMove(static_cast<enum Action>(int_action));
					}
					break;
				case e_action_shot:
					{
						ptr_playground->PlayerShot();
					}
					break;
				default:
					break;
			}
		}
		ptr_playground->UpdateCreatures();
		ptr_playground->PrintToConsole();
	}
}

int main()
{
	PlayGame();
}
