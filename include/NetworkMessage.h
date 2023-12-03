//
// Created by lukasz on 03.12.23.
//

#include <string>
#include <utility>

#ifndef BLOCKCHAIN_NETWORKMESSAGE_H
#define BLOCKCHAIN_NETWORKMESSAGE_H

struct NetworkMessage {
    NetworkMessage() = default;
    NetworkMessage(std::string  senderIp, std::string  receiverIp, std::string  message) : senderIp(std::move(senderIp)), receiverIp(std::move(receiverIp)), message(std::move(message)) {}
    std::string senderIp;
    std::string receiverIp;
    std::string message;
};

#endif //BLOCKCHAIN_NETWORKMESSAGE_H
