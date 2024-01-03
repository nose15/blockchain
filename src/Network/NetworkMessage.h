//
// Created by lukasz on 03.12.23.
//

#include <string>
#include <utility>
#include <random>
#include "../Address.h"
#include "../../external/nlohmann/json.hpp"
using json = nlohmann::json;

#ifndef BLOCKCHAIN_NETWORKMESSAGE_H
#define BLOCKCHAIN_NETWORKMESSAGE_H

enum MessageType {
    Broadcast,
    Request,
    Response,
    Ping,
};


class NetworkMessage {
private:
    unsigned int m_id = 0;
    Address m_senderAddress = Address("0", "0");
    Address m_receiverAddress = Address("0", "0");
    MessageType m_messageType = Ping;
    std::string m_endpoint = "/";
    std::string m_body = " ";

public:
    NetworkMessage() = default;
    NetworkMessage(unsigned int id, MessageType type, Address senderAddress, Address receiverAddress, std::string message);
    NetworkMessage(unsigned int id, Address senderAddress, Address receiverAddress, std::string message);
    unsigned int Id();
    std::string Body();
    std::string EndPoint();
    MessageType Type();
    Address SenderAddress();
    Address ReceiverAddress();
    json Json();
};

#endif //BLOCKCHAIN_NETWORKMESSAGE_H
