//
// Created by lukasz on 03.12.23.
//

#include "./Address.h"
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
    NetworkMessage(unsigned int id, MessageType type, Address senderAddress, Address receiverAddress, std::string body) : m_id(id), m_messageType(type), m_senderAddress(std::move(senderAddress)), m_receiverAddress(std::move(receiverAddress)), m_body(std::move(body)) {}
    NetworkMessage(unsigned int id, Address senderAddress, Address receiverAddress, std::string body) : m_id(id), m_senderAddress(std::move(senderAddress)), m_receiverAddress(std::move(receiverAddress)), m_body(std::move(body)) { m_messageType = Request; }

    unsigned int m_id = 0;
    Address m_senderAddress = Address("0", "0");
    Address m_receiverAddress = Address("0", "0");;
    MessageType m_messageType = Ping;
    std::string m_endpoint = "/";
    std::string m_body = "A";
};

#endif //BLOCKCHAIN_NETWORKMESSAGE_H
