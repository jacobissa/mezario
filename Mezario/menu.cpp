#include "menu.h"
#include "file.h"
#include "Mezario.h"

#include <iostream>
#include <conio.h>

int Menu::currently_selected[] = {1, 0, 0};

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
        currently_selected[1] = (user_input == KEY_DOWN) ? 1 : 0;
        currently_selected[2] = (user_input == KEY_UP) ? 1 : 0;
    }
    else if (currently_selected[1] == 1) {
        currently_selected[0] = (user_input == KEY_UP) ? 1 : 0;
        currently_selected[1] = 0;
        currently_selected[2] = (user_input == KEY_DOWN) ? 1 : 0;
    }
    else { // [2] == 1
        currently_selected[0] = (user_input == KEY_DOWN) ? 1 : 0;
        currently_selected[1] = (user_input == KEY_UP) ? 1 : 0;
        currently_selected[2] = 0;
    }
}

void Menu::draw(const HANDLE& h_console) {
    system("cls");
    SetConsoleTextAttribute(h_console , Color::e_color_yellow);

    File file("info.mezario");
    if (!file.file_exists()) {
        std::cout << "It seems like it's your first time here." << "\n";
        std::cout << "Please tell me your name: ";

        std::string user_name;
        std::cin >> user_name;

        std::cout << user_name;
        file.write_file(PLAYER_NAME, user_name);

        // new player does not have a highscore yet
        file.write_file(PLAYER_HIGHSCORE, "0");
        file.write_file(PLAYER_LEVEL, "1");
        file.write_file(PLAYER_REACHED_LEVEL, "1");
    }

    system("cls");
    std::cout << "Welcome to Mezario, " << file.get_name_of_player() << "!\n\n";

    int current_level = file.get_current_level();
    
    if (current_level == 1) {
        print_menu_option(h_console, "Play Mezario", currently_selected[0]);
    } else {
        std::string option = std::string("Continue playing on level ").append(std::to_string(current_level));
        print_menu_option(h_console, option, currently_selected[0]);
    }

    print_menu_option(h_console, "Level Select", currently_selected[1]);
    print_menu_option(h_console, "Exit", currently_selected[2]);

    SetConsoleTextAttribute(h_console, Color::e_color_cyan);
    std::cout << "\n\nYour highscore: " << file.get_highscore_of_player();
}

void Menu::draw_lvl_select(const HANDLE& h_console, const int selected_lvl)
{
    system("cls");
    File file("info.mezario");

    SetConsoleTextAttribute(h_console, Color::e_color_yellow);

    std::cout << file.get_name_of_player() << "... choose a level you want to play!\n";
    std::cout << "You can only play levels you already completed.\n\n";

    for (int i = 1; i <= 5; i++) {
        if (i > file.get_reached_level()) {
            SetConsoleTextAttribute(h_console, Color::e_color_red);
        }

        print_menu_option(h_console, "Level " + std::to_string(i), selected_lvl == i);
    }

    SetConsoleTextAttribute(h_console, Color::e_color_yellow);
    std::cout << "\n\nConfirm your choice with (ENTER).\n";
}

Options Menu::evaluate_player_input() {
    system("cls");

    if (currently_selected[0] == 1) {
        return PLAY_GAME;
    } else if (currently_selected[1] == 1) {
        return LEVEL_SELECT;
    }

    return EXIT;
}

Options Menu::print_menu(const HANDLE& h_console) {
    File file("info.mezario");

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

    Options player_choice = evaluate_player_input();

    if (player_choice == LEVEL_SELECT) {
        draw_lvl_select(h_console, file.get_current_level());

        int user_input;
        int lvl;
        do {
            user_input = _getch();
            
            if ((user_input <= 0 + 48 || user_input > 6 + 48) || user_input - 48 > file.get_reached_level()) {
                continue;
            } else {
                lvl = user_input - 48;
            }

            draw_lvl_select(h_console, user_input - 48);
        } while (user_input != ENTER);

        file.update_level(lvl);
        system("cls");

        return PLAY_GAME;
    }

    return player_choice;
}
