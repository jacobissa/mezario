#include "Mezario.h"
#include "Playground.h"
#include "Player.h"

const HANDLE& ConsoleSettings()
{
	const HANDLE& h_console = GetStdHandle(STD_OUTPUT_HANDLE);
	MoveWindow(GetConsoleWindow() , 0 , 0 , 440 , 500 , true);
	SetConsoleTitleA("Mezario");
	const CONSOLE_CURSOR_INFO cursor_info{ 1, FALSE };
	SetConsoleCursorInfo(h_console , &cursor_info);
	CONSOLE_FONT_INFOEX font{};
	font.cbSize = sizeof(font);
	font.nFont = 0;
	font.dwFontSize.X = 25;
	font.dwFontSize.Y = 25;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_MEDIUM;
	SetCurrentConsoleFontEx(h_console , TRUE , &font);
	srand(static_cast<unsigned int>( time(NULL) ));
	return h_console;
}

void PlayGame(const HANDLE& h_console)
{
	const int i_width = 50;
	const int i_height = 25;
	const int i_probability_wall = 25;
	const int i_quantity_enemy = 9;
	PlaygroundPtr ptr_playground = std::make_shared<Playground>(i_height , i_width , i_probability_wall , i_quantity_enemy);
	enum Action e_action;

	while ( true )
	{
		SetConsoleCursorPosition(h_console , { 0,0 });
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
					break;
			}
		}
		ptr_playground->UpdateCreatures();
		ptr_playground->PrintToConsole(h_console);
	}
}

int main()
{
	const HANDLE h_console = ConsoleSettings();
	PlayGame(h_console);
}
