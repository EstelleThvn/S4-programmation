#include "play_guess_the_number.hpp"
#include <iostream>
#include <random>

//picks a random number between the min and the max
int pick_random_number(int min, int max)
{
    static std::default_random_engine  generator{std::random_device{}()};
    std::uniform_int_distribution<int> distribution{min, max};
    return distribution(generator);
}

//gets the number the user has chosen
int get_user_number()
{
    int user_number;

    while (std::cout << "Enter a number: " && !(std::cin >> user_number)) {
        std::cin.clear();                                                   //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input, please re-enter\n";
    }

    return user_number;
}

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

//main function of the game
void play_guess_the_number()
{
    const int min            = 0;
    const int max            = 100;
    int       correct_number = pick_random_number(min, max);

    std::cout << "Pick a random number between " << min << " and " << max << std::endl;

    bool finished = false;
    while (!finished) {
        int user_number = get_user_number();

        if (user_number == correct_number) {
            finished = true;
        }
        else {
            compare_user_number_to_correct_answer(correct_number, user_number);
        }
    }

    std::cout << "Congrats, you won!" << std::endl;
}