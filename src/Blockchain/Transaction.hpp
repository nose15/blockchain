//
// Created by lukol on 04.12.2023.
//

#include <string>
#include <cstdint>

#ifndef BLOCKCHAIN_TRANSACTION_H
#define BLOCKCHAIN_TRANSACTION_H

namespace Blockchain {
	struct Transaction {
		uint32_t amount;
		uint8_t senderId;
		uint8_t receiverId;
		Transaction(uint8_t senderId, uint8_t receiverId, uint32_t amount);
	};
}



#endif //BLOCKCHAIN_TRANSACTION_H
