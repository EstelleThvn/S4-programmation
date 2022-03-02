#pragma once

template<typename T>
T get_input_from_user()
{
    T user_input;

    while (std::cout << "Enter: " && !(std::cin >> user_input)) {
        std::cin.clear();                                                   //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input, please re-enter\n";
    }

    return user_input;
}