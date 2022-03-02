#pragma once
#include <string>
#include <vector>

struct hangman_state {
    int               number_of_lives = 8;
    std::string       word_to_guess;
    std::vector<char> letters_that_have_been_found;
};

void        play_hangman();
std::string pick_a_word_to_guess();
void        show_number_of_lives(int number_of_lives);
bool        player_is_alive(int number_of_lives);
bool        player_has_won(const std::vector<bool>& letters_guessed);
void        show_word_to_guess_with_missing_letters(const std::string& word, const std::vector<bool>& letters_guessed);