#include "play_hangman.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include "../common/common.hpp"
#include "../common/get_input_from_user.h"

//**********************************************************************//
//**************************** Declarations ****************************//
//**********************************************************************//

std::string       pick_a_word_to_guess();
std::vector<bool> initialize_letters_guessed(const std::string& word_to_guess);

struct HangmanState {
    int               number_of_lives;
    std::string       word_to_guess;
    std::vector<bool> letters_that_have_been_found;

    HangmanState()
        : number_of_lives(8), word_to_guess(pick_a_word_to_guess()), letters_that_have_been_found(initialize_letters_guessed(word_to_guess))
    {
    }
};

void show_number_of_lives(int number_of_lives);
bool player_is_alive(int number_of_lives);
bool player_has_won(const std::vector<bool>& letters_guessed);
void show_word_to_guess_with_missing_letters(const std::string& word, const std::vector<bool>& letters_guessed);
bool word_contains(char letter, std::string word);
void mark_as_guessed(char guessed_letter, std::vector<bool>& letters_guessed, const std::string& word_to_guess);
void remove_one_life(int& lives_count);
void show_congrats_message();
void show_defeat_message();
void show_answer_message(const std::string& word_to_guess);

//**********************************************************************//
//**********************************************************************//
//**********************************************************************//

//main function to play the game
void play_hangman()
{
    HangmanState hangman_party;

    pick_a_word_to_guess();
    while (player_is_alive(hangman_party.number_of_lives) && !player_has_won(hangman_party.letters_that_have_been_found)) {
        show_number_of_lives(hangman_party.number_of_lives);
        show_word_to_guess_with_missing_letters(hangman_party.word_to_guess, hangman_party.letters_that_have_been_found);
        const auto guess = get_input_from_user<char>();
        if (word_contains(guess, hangman_party.word_to_guess)) {
            mark_as_guessed(guess, hangman_party.letters_that_have_been_found, hangman_party.word_to_guess);
        }
        else {
            remove_one_life(hangman_party.number_of_lives);
        }
    }
    if (player_has_won(hangman_party.letters_that_have_been_found)) {
        show_congrats_message();
    }
    else {
        show_defeat_message();
    }
    show_answer_message(hangman_party.word_to_guess);
}

//selects a random word that the player will have to guess, from a lsit of words
std::string pick_a_word_to_guess()
{
    const std::array words = {"code", "crous", "imac", "opengl"};

    return words[pick_random_number<int>(0, words.size() - 1)];
}

std::vector<bool> initialize_letters_guessed(const std::string& word_to_guess)
{
    return std::vector<bool>(word_to_guess.size(), false);
}

//displays the number of lives the player has left
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
    return std::all_of(letters_guessed.begin(), letters_guessed.end(), [](bool letter_guessed) {
        return letter_guessed == true;
    });
}

void show_word_to_guess_with_missing_letters(const std::string& word, const std::vector<bool>& letters_guessed)
{
    for (size_t i = 0; i < letters_guessed.size(); i++) {
        if (letters_guessed[i]) {
            std::cout << word.at(i);
        }
        else {
            std::cout << "_";
        }
    }
    std::cout << std::endl;
}

bool word_contains(char letter, std::string word)
{
    return word.find(letter) != std::string::npos;
}

void mark_as_guessed(char guessed_letter, std::vector<bool>& letters_guessed, const std::string& word_to_guess)
{
    for (size_t i = 0; i < letters_guessed.size(); i++) {
        if (word_to_guess.at(i) == guessed_letter) {
            letters_guessed[i] = true;
        }
    }
}

void remove_one_life(int& lives_count)
{
    lives_count--;
}

void show_congrats_message()
{
    std::cout << "Congrats, you won!" << std::endl;
}
void show_defeat_message()
{
    std::cout << "Sorry, you lost!" << std::endl;
}

void show_answer_message(const std::string& word_to_guess)
{
    std::cout << "The word was " << word_to_guess << std::endl;
}