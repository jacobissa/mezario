#include "menu.h"
#include "Mezario.h"

#include <iostream>
#include <conio.h>

int Menu::currently_selected[] = {1, 0};

void Menu::print_menu_option(const HANDLE& h_console, std::string option, bool is_selected) {
    if (is_selected) {
        SetConsoleTextAttribute(h_console , Color::e_color_green);
        std::cout << ">\t";
    } else {
        std::cout << " \t";
    }

    std::cout << option << std::endl;
    SetConsoleTextAttribute(h_console , Color::e_color_yellow);
}

void Menu::cycle(int user_input) {
    if (currently_selected[0] == 1) {
        currently_selected[0] = 0;
        currently_selected[1] = 1;
    } else if (currently_selected[1] == 1) {
        currently_selected[0] = 1;
        currently_selected[1] = 0;
    }
}

void Menu::draw(const HANDLE& h_console) {
    system("cls");
    SetConsoleTextAttribute(h_console , Color::e_color_yellow);
    std::cout << "Welcome to Mezario!\n\n";

    print_menu_option(h_console, "Play Mezario", currently_selected[0]);
    print_menu_option(h_console, "Exit", currently_selected[1]);
}

Options Menu::evaluate_player_input() {
    system("cls");

    if (currently_selected[0] == 1) {
        return PLAY_GAME;
    }

    return EXIT;
}

Options Menu::print_menu(const HANDLE& h_console) {
    // Initial draw
    draw(h_console);

    int user_input;
    do {
        user_input = _getch();

        if (user_input != KEY_UP && user_input != KEY_DOWN) {
            continue;
        }

        cycle(user_input);
        draw(h_console);
    } while(user_input != ENTER);

    return evaluate_player_input();
}
