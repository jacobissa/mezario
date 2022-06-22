#ifndef MENU_H
#define MENU_H

#include <Windows.h>
#include <string>

enum Options { PLAY_GAME, OPTIONS, EXIT };

enum UserInput {
    ENTER = 13,
    KEY_UP = 72,
    KEY_DOWN = 80
};

class Menu
{
private:
     static int currently_selected[];
     static void print_menu_option(const HANDLE& h_console, std::string option,  bool is_selected);
     static void cycle(int user_input);
     static void draw(const HANDLE& h_console);
     static Options evaluate_player_input();

public:
    static Options print_menu(const HANDLE& h_console);
};

#endif // MENU_H
