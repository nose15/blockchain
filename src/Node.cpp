//
// Created by lukol on 26.11.2023.
//

#include <utility>

#include "../include/Node.h"

Node::Node(std::string id, Network * network) : m_id(std::move(id))
{
    std::cout << "Node " << m_id << " created" << std::endl;
    this->networkClient = new NetworkClient(this->m_id, network);
}

std::string Node::getId()
{
    return m_id;
}

void Node::ping(std::string receiverIp)
{
    networkClient->sendMessage(std::move(receiverIp), "ping");
}