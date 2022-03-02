#include "play_hangman.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include "../common/common.hpp"
#include "../common/get_input_from_user.h"

std::string pick_a_word_to_guess()
{
    const std::array words = {"code", "crous", "imac", "opengl"};

    return words[pick_random_number<int>(0, words.size() - 1)];
}

void play_hangman()
{
    hangman_state hangman_party;
    hangman_party.word_to_guess = pick_a_word_to_guess();
    show_number_of_lives(hangman_party.number_of_lives);
    std::string user_letter = get_input_from_user<std::string>();
}

void show_number_of_lives(int number_of_lives)
{
    std::cout << "You have " << number_of_lives << " lives" << std::endl;
}

bool player_is_alive(int number_of_lives)
{
    return (number_of_lives > 0) ? true : false;
}

bool player_has_won(const std::vector<bool>& letters_guessed)
{
    /*int number_of_letters_guessed = 0;
    for (int i = 0; i < letters_guessed.size(); i++) {
        if (letters_guessed[i] == true) {
            number_of_letters_guessed++;
        }
    }
    return (number_of_letters_guessed = letters_guessed.size()) ? true : false;*/
    return std::all_of(letters_guessed.begin(), letters_guessed.end(), [](bool letter_guessed) {
        return letter_guessed;
    });
}

void show_word_to_guess_with_missing_letters(const std::string& word, const std::vector<bool>& letters_guessed)
{
    for (size_t i = 0; i < letters_guessed.size(); i++) {
        if (letters_guessed[i] == true) {
            std::cout << word.at(i);
        }
        else {
            std::cout << "_";
        }
    }
    std::cout << std::endl;
}