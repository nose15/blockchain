//
// Created by lukol on 11.12.2023.
//

#include <string>

#ifndef BLOCKCHAIN_ADDRESS_H
#define BLOCKCHAIN_ADDRESS_H

struct Address {
    std::string ip;
    std::string port;

    Address() = default;
    Address(std::string ip, std::string port) : ip(ip), port(port) {}
};

#endif //BLOCKCHAIN_ADDRESS_H
