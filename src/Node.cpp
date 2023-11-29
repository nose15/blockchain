//
// Created by lukol on 26.11.2023.
//

#include "../include/Node.h"

Node::Node(std::string id) : m_id(std::move(id))
{
    std::cout << "Node " << m_id << " created" << std::endl;
}

void Node::triggerReceive(std::string message)
{
    std::cout << "Node " << m_id << " received a message: '" << message << "'" << std::endl;

    network->send(this->m_id, message, this->m_id);
}

void Node::ping(std::string receiver_id)
{
    std::string message = this->m_id;
    network->send(m_id, std::move(receiver_id), message);
}

void Node::setNetwork(Network &newNetwork)
{
    this->network = &newNetwork;
}

std::string Node::getId()
{
    return m_id;
}