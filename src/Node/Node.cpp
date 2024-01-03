//
// Created by lukol on 26.11.2023.
//

#include "Node.h"

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
void Node::Ping(const Address & receiverAddress)
{
    NetworkMessage response = networkClient->SendRequest(receiverAddress, "8000", R"({"message": "ping"})");
    json body = response.Json();
    std::cout << this->m_id << " ping " << receiverAddress.ip << ":" << receiverAddress.port << " => " << body["message"] << std::endl;
}

void Node::RequestTest() {
    NetworkMessage response = this->networkClient->SendRequest(Address("2", "8000"), "8000", R"({"message": "request1"})");
}

void Node::BlockchainTest(const std::vector<Address>& initialPeers) {
    this->blockchainClient->DiscoverPeers(initialPeers);
}

void Node::BlockchainTransactionTest(std::string receiverId, int amount)
{
    blockchainClient->MakeTransaction(receiverId, amount);
}

