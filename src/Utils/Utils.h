//
// Created by lukasz on 08.12.23.
//

#include <random>
#include <map>
#include "../Address.h"
#include <iostream>
#include <string>


#ifndef BLOCKCHAIN_UTILS_H
#define BLOCKCHAIN_UTILS_H

class Utils {
public:
    static unsigned int generateRandomId();

    static std::vector<std::string> SplitString(const std::string& str, char separator, uint32_t target_count);
    static void PrintMap(const std::map<std::string, Address> &peerMap);
};


#endif //BLOCKCHAIN_UTILS_H
