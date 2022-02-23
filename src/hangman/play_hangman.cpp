#include "play_hangman.hpp"
#include <array>
#include <iostream>
#include <string>

std::string pick_a_work_to_guess()
{
    const std::array words = {"code", "crous", "imac", "opengl"};

    return words[1];
}