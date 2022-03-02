#pragma once
#include <random>

template<typename T>
T pick_random_number(T min, T max)
{
    static std::default_random_engine generator{std::random_device{}()};
    std::uniform_int_distribution<T>  distribution{min, max};
    return distribution(generator);
}