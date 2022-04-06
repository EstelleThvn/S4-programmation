#include "play_guess_the_number.hpp"
#include <iostream>
#include <random>
#include "../common/common.hpp"
#include "../common/get_input_from_user.h"

//compares the number the user entered with the number randomly chosen by the program
void compare_user_number_to_correct_answer(int correct_number, int user_number)
{
    if (correct_number > user_number) {
        std::cout << "Greater" << std::endl;
    }
    else if (correct_number < user_number) {
        std::cout << "Smaller" << std::endl;
    }
}

void play_guess_the_number()
{
    const int  min            = 0;
    const int  max            = 100;
    const auto correct_number = pick_random_number<int>(min, max);

    std::cout << "Pick a random number between " << min << " and " << max << std::endl;

    bool finished          = false;
    int  number_of_guesses = 0;

    while (!finished) {
        const auto user_number = get_input_from_user<int>();

        if (user_number == correct_number) {
            finished = true;
        }
        else {
            compare_user_number_to_correct_answer(correct_number, user_number);
        }
        number_of_guesses++;
    }

    std::cout << "Congrats, you won!" << std::endl;
    std::cout << "It took you " << number_of_guesses << " guesses to find the number" << std::endl;
}