//
// Created by lukasz on 08.12.23.
//

#include <random>
#include <map>
#include <Address.hpp>
#include <iostream>
#include <string>

#ifndef BLOCKCHAIN_UTILS_H
#define BLOCKCHAIN_UTILS_H

namespace Utils {
	uint32_t generateRandomId();

	std::vector<std::string> SplitString(const std::string & str, char separator, uint32_t target_count);

	void PrintMap(const std::map<uint8_t, Address> & peerMap);
};


#endif //BLOCKCHAIN_UTILS_H
