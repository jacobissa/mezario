#include "Mezario.h"

#include <conio.h>
#include <iostream>
#include <Windows.h>

#include "Playground.h"

void ConsoleSettings(const HANDLE& h_console)
{
	MoveWindow(GetConsoleWindow() , 0 , 0 , 440 , 600 , FALSE);
	SetConsoleTitleA("Mezario");
	constexpr CONSOLE_CURSOR_INFO cursor_info{ 1, FALSE };
	SetConsoleCursorInfo(h_console , &cursor_info);
	CONSOLE_FONT_INFOEX font{};
	font.cbSize = sizeof(font);
	font.nFont = 0;
	font.dwFontSize.X = 25;
	font.dwFontSize.Y = 25;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_MEDIUM;
	SetCurrentConsoleFontEx(h_console , TRUE , &font);
	srand(static_cast<unsigned>( time(nullptr) ));
}

bool PlayGame(const HANDLE& h_console)
{
	constexpr int i_width = 50;
	constexpr int i_height = 25;
	constexpr int i_hearts = 5;
	constexpr int i_probability_wall = 25;
	constexpr int i_quantity_enemy = 12;
	constexpr int i_time_max = 90;
	const PlaygroundPtr ptr_playground = std::make_shared<Playground>(i_height , i_width , i_hearts , i_probability_wall , i_quantity_enemy , i_time_max);
	bool b_start_play = false;
	while ( true )
	{
		SetConsoleCursorPosition(h_console , { 0,0 });
		while ( _kbhit() )
		{
			const Action e_action = static_cast<Action>( _getch() );
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
		std::cout << "\tTIME:    " << ptr_playground->GetTimeLeft() << "   " << std::endl;
		std::cout << "\tHEARTS:  " << ptr_playground->GetHearts() << "   " << std::endl;
		std::cout << "\tENEMIES: " << ptr_playground->GetEnemies() << "   " << std::endl;

		if ( ptr_playground->IsWin() ) return true;
		if ( ptr_playground->IsLose() ) return false;

		while ( !b_start_play )
		{
			while ( _kbhit() )
			{
				const Action e_action = static_cast<Action>( _getch() );
				switch ( e_action )
				{
					case Action::e_action_up:
					case Action::e_action_down:
					case Action::e_action_left:
					case Action::e_action_right:
						{
							b_start_play = true;
							ptr_playground->PlayerMove(e_action);
						}
						break;
					default:
						break;
				}
			}
		}
	}
}

bool PlayAgain(const bool b_win)
{
	if ( b_win )
	{
		std::cout << "You Win! Do you want to play again? (Y/N)" << std::endl;
	}
	else
	{
		std::cout << "Game over! Do you want to play again? (Y/N)" << std::endl;
	}
	while ( true )
	{
		while ( _kbhit() )
		{
			const Action e_action = static_cast<Action>( _getch() );
			switch ( e_action )
			{
				case Action::e_action_yes:
					{
						return true;
					}
				case Action::e_action_no:
					{
						return false;
					}
				default: ;
			}
		}
	}
}


int main()
{
	const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleSettings(h_console);

	bool b_play_game = true;
	while ( b_play_game )
	{
		const bool b_game_result = PlayGame(h_console);
		b_play_game = PlayAgain(b_game_result);
		system("CLS");
	}
	return 0;
}
