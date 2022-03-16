#pragma once
#include <string>
#include <vector>

struct HangmanState {
    int               number_of_lives = 8;
    std::string       word_to_guess;
    std::vector<bool> letters_that_have_been_found;
};

void              play_hangman();
std::string       pick_a_word_to_guess();
std::vector<bool> initialize_letters_guessed(const std::string& word_to_guess);
void              show_number_of_lives(int number_of_lives);
bool              player_is_alive(int number_of_lives);
bool              player_has_won(const std::vector<bool>& letters_guessed);
void              show_word_to_guess_with_missing_letters(const std::string& word, const std::vector<bool>& letters_guessed);
bool              word_contains(char letter, std::string word);
void              mark_as_guessed(char guessed_letter, std::vector<bool>& letters_guessed, const std::string& word_to_guess);
void              remove_one_life(int& lives_count);
void              show_congrats_message();
void              show_defeat_message();
void              show_answer_message(const std::string& word_to_guess);