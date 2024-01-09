//
// Created by lukol on 04.12.2023.
//

#include <string>
#include <cstdint>

#ifndef BLOCKCHAIN_TRANSACTION_H
#define BLOCKCHAIN_TRANSACTION_H


class Transaction {
private:
	int amount;
	std::string senderId;
	std::string receiverId;
public:
	Transaction(std::string &, std::string &, uint32_t);

	std::string to_string();
};


#endif //BLOCKCHAIN_TRANSACTION_H
