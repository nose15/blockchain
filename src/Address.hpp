//
// Created by lukol on 11.12.2023.
//

#include <string>
#include <iostream>

#ifndef BLOCKCHAIN_ADDRESS_H
#define BLOCKCHAIN_ADDRESS_H

struct Address {
	uint8_t ip;
	uint16_t port;

	Address() = default;

	Address(uint8_t ip, uint16_t port) : ip(ip), port(port)
	{
		std::cout << sizeof(*this) << std::endl;
	}
};

#endif //BLOCKCHAIN_ADDRESS_H
