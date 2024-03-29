//
// Created by lukasz on 08.12.23.
//

#include <Utils/Utils.hpp>

namespace Utils {
	uint32_t generateRandomId() {
		//WARNING: THIS IS NOT CRYPTOGRAPHICALLY SECURE
		//TODO: Implement a more cryptographically secure solution
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<uint32_t> dis(1, std::numeric_limits<int>::max());

		return dis(gen);
	}

	std::vector<std::string> SplitString(const std::string & str, char separator, uint32_t target_count = 0) {
		uint32_t count = target_count;
		std::vector<std::string> result = {};

		std::string currentString;
		for (char currentChar: str) {
			if (currentChar == separator && count != 0) {
				result.push_back(currentString);
				currentString = "";
				count--;
				continue;
			}

			currentString += currentChar;
		}

		if (!currentString.empty()) {
			result.push_back(currentString);
		}

		return result;
	}

	void PrintMap(const std::map<uint8_t, Address> & peerMap) {
		for (const auto & pair: peerMap) {
			std::cout << std::to_string(pair.first) + " " + std::to_string(pair.second.ip) + ":" + std::to_string(pair.second.port) + "; ";
		}

		std::cout << std::endl;
	}

}
