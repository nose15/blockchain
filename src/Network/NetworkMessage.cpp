//
// Created by lukasz on 15.12.23.
//

#include "../../include/Network/NetworkMessage.h"

NetworkMessage::NetworkMessage(unsigned int id, MessageType type, Address senderAddress, Address receiverAddress, std::string body) : m_id(id), m_messageType(type), m_senderAddress(std::move(senderAddress)), m_receiverAddress(std::move(receiverAddress)), m_body(std::move(body))
{

}

NetworkMessage::NetworkMessage(unsigned int id, Address senderAddress, Address receiverAddress, std::string body) : m_id(id), m_senderAddress(std::move(senderAddress)), m_receiverAddress(std::move(receiverAddress)), m_body(std::move(body))
{
    m_messageType = Request;
}

unsigned int NetworkMessage::Id()
{
    return this->m_id;
}

std::string NetworkMessage::Body()
{
    return this->m_body;
}

json NetworkMessage::Json() {
    return json::parse(this->m_body);
}

std::string NetworkMessage::EndPoint()
{
    return this->m_endpoint;
}

MessageType NetworkMessage::Type()
{
    return this->m_messageType;
}

Address NetworkMessage::SenderAddress()
{
    return this->m_senderAddress;
}

Address NetworkMessage::ReceiverAddress()
{
    return this->m_receiverAddress;
}