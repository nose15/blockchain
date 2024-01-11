//
// Created by lukol on 04.12.2023.
//

#include <Blockchain/Transaction.hpp>

namespace Blockchain {
	Transaction::Transaction(uint8_t senderId, uint8_t receiverId, uint32_t amount) : senderId(senderId), receiverId(receiverId), amount(amount) {}
}
