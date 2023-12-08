//
// Created by lukasz on 08.12.23.
//

#include "../include/Utils.h"
#include <random>

unsigned int Utils::generateRandomId()
{
    //WARNING: THIS IS NOT CRYPTOGRAPHICALLY SECURE
    //TODO: Implement a more cryptographically secure solution
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dis(1, std::numeric_limits<int>::max());

    return dis(gen);
}