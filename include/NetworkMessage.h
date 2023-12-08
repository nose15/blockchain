//
// Created by lukasz on 03.12.23.
//

#include <string>
#include <utility>
#include <random>

#ifndef BLOCKCHAIN_NETWORKMESSAGE_H
#define BLOCKCHAIN_NETWORKMESSAGE_H

enum MessageType {
    Broadcast,
    Request,
    Response,
    Ping,
};


struct NetworkMessage {
    NetworkMessage() = default;
    NetworkMessage(std::string senderIp, std::string receiverIp, std::string message, std::string port, unsigned int id, MessageType type) : senderIp(std::move(senderIp)), receiverIp(std::move(receiverIp)), message(std::move(message)), port(std::move(port)), id(id), m_messageType(type) {}
    NetworkMessage(std::string senderIp, std::string receiverIp, std::string message, std::string port) : senderIp(std::move(senderIp)), receiverIp(std::move(receiverIp)), message(std::move(message)), port(std::move(port)) {}
    NetworkMessage(std::string senderIp, std::string receiverIp, std::string message) : senderIp(std::move(senderIp)), receiverIp(std::move(receiverIp)), message(std::move(message)) { this->port = ""; }

    unsigned int id;
    MessageType m_messageType;
    std::string endpoint;
    std::string senderIp;
    std::string receiverIp;
    std::string message;
    std::string port;
};

#endif //BLOCKCHAIN_NETWORKMESSAGE_H
