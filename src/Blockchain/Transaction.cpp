//
// Created by lukol on 04.12.2023.
//

#include "Transaction.h"
Transaction::Transaction(std::string &senderIp, std::string &receiverIp, int amount) : senderId(senderIp), receiverId(receiverIp), amount(amount) {}

std::string Transaction::to_string() {
    return senderId + " " + receiverId + " " + std::to_string(amount);
}