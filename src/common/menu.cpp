#include "menu.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include "../guess_the_number/play_guess_the_number.hpp"
#include "../hangman/play_hangman.hpp"
#include "../noughts_and_crosses/play_noughts_and_crosses.hpp"
#include "get_input_from_user.h"

struct Game {
    std::string           name;
    std::function<void()> function_to_call;

    Game(std::string name, std::function<void()> function_to_call)
        : name(name), function_to_call(function_to_call)
    {
    }
};

void show_the_list_of_commands(std::vector<Game>& games)
{
    std::cout << std::endl;
    std::cout << "************************" << std::endl;
    std::cout << "********* MENU *********" << std::endl;
    std::cout << "************************" << std::endl;

    std::cout << "What do you want to do?" << std::endl;
    for (size_t i = 0; i < games.size(); i++) {
        std::cout << i << " : " << games[i].name << std::endl;
    }
    std::cout << "q : Quit" << std::endl;

    std::cout << std::endl;
}

void display_exit_the_menu()
{
    std::cout << "************************" << std::endl;
    std::cout << "************************" << std::endl;
    std::cout << std::endl;
}

void play_a_game(int game_number, std::vector<Game>& games)
{
    display_exit_the_menu();
    games[game_number].function_to_call();
}

void game()
{
    std::vector<Game> games;
    Game              guess_the_number("guess_the_number", play_guess_the_number);
    Game              hangman("hangman", play_hangman);
    Game              noughts_and_crosses("Noughts and Crosses", play_noughts_and_crosses);
    games.push_back(guess_the_number);
    games.push_back(hangman);
    games.push_back(noughts_and_crosses);

    bool playing = true;
    while (playing) {
        show_the_list_of_commands(games);
        auto user_game_choice = get_input_from_user<char>();

        if (user_game_choice == 'q') {
            playing = false;
        }
        else {
            if ((size_t)(user_game_choice - 48) < games.size()) {
                play_a_game(user_game_choice - 48, games);
            }
            else {
                std::cout << "Sorry I don't know that command!" << std::endl;
            }
        }
    }
}