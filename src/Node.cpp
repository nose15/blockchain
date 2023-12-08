//
// Created by lukol on 26.11.2023.
//

#include "../include/Node.h"

Node::Node(std::string id, Network * network) : m_id(std::move(id))
{
    std::cout << "Node " << m_id << " created" << std::endl;
    this->networkClient = new NetworkClient(this->m_id, network);
    // TODO: Update so it gets initial peers
    this->blockchainClient = new BlockchainClient(networkClient);
}

std::string Node::getId()
{
    return m_id;
}


//TODO: Implement some UI
void Node::ping(const std::string& receiverIp)
{
    NetworkMessage response = networkClient->SendRequest(receiverIp, "0", "ping");
    std::cout << this->m_id << " ping " << receiverIp << ": " << response.message << std::endl;
}


void Node::transaction(std::string receiverId, int amount)
{
    blockchainClient->MakeTransaction(receiverId, amount);
}

void Node::Request() {
    NetworkMessage response = this->networkClient->SendRequest("2", "0", "R");
    std::cout << response.message << std::endl;
}
