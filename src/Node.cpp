//
// Created by lukol on 26.11.2023.
//

#include "../include/Node.h"

Node::Node(std::string id, Network * network) : m_id(std::move(id))
{
    std::cout << "Node " << m_id << " created" << std::endl;
    this->networkClient = new NetworkClient(this->m_id, network);
    this->blockchainClient = new BlockchainClient(networkClient);
}

std::string Node::getId()
{
    return m_id;
}

void Node::ping(const std::string& receiverIp)
{
    networkClient->SendMessage(receiverIp, "0", "ping");
}


void Node::transaction(std::string receiverId, int amount)
{
    blockchainClient->MakeTransaction(receiverId, amount);
}
