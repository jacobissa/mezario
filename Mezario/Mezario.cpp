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
	enum Action e_action;

	while ( true )
	{
		SetConsoleCursorPosition(h_console , cursor_position);
		while ( _kbhit() )
		{
			e_action = static_cast<enum Action>( _getch() );
			switch ( e_action )
			{
				case Action::e_action_up:
				case Action::e_action_down:
				case Action::e_action_left:
				case Action::e_action_right:
					{
						ptr_playground->PlayerMove(e_action);
					}
					break;
				case Action::e_action_shot:
					{
						ptr_playground->PlayerShot();
					}
					break;
				default:
					std::cout << e_action << std::endl;
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
