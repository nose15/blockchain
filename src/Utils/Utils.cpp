//
// Created by lukasz on 08.12.23.
//

#include "Utils.h"

unsigned int Utils::generateRandomId()
{
    //WARNING: THIS IS NOT CRYPTOGRAPHICALLY SECURE
    //TODO: Implement a more cryptographically secure solution
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dis(1, std::numeric_limits<int>::max());

    return dis(gen);
}

std::vector<std::string> Utils::SplitString(const std::string& str, char separator) {
    std::vector<std::string> result = {};

    std::string currentString;
    for (char currentChar: str)
    {
        if (currentChar == separator) {
            result.push_back(currentString);
            currentString = "";
            continue;
        }

        currentString += currentChar;
    }

    if (!currentString.empty())
    {
        result.push_back(currentString);
    }

    return result;
}
