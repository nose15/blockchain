//
// Created by lukasz on 03.12.23.
//

#include <string>
#include <utility>

#ifndef BLOCKCHAIN_NETWORKMESSAGE_H
#define BLOCKCHAIN_NETWORKMESSAGE_H

struct NetworkMessage {
    NetworkMessage() = default;
    NetworkMessage(std::string senderIp, std::string receiverIp, std::string message, std::string port) : senderIp(std::move(senderIp)), receiverIp(std::move(receiverIp)), message(std::move(message)), port(std::move(port)) {}
    std::string senderIp;
    std::string receiverIp;
    std::string message;
    std::string port;
};

#endif //BLOCKCHAIN_NETWORKMESSAGE_H
