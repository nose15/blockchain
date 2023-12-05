//
// Created by lukasz on 02.12.23.
//

#include <string>
#include "../include/BlockchainClient.h"
#include <map>

BlockchainClient::BlockchainClient(NetworkClient * networkClient) : networkClient(networkClient)
{
    this->id = networkClient->getIp(); // temporary solution - TODO: More sophisticated id generation
    networkClient->addPortHandler("8000", [this](NetworkMessage& networkMessage) {this->MessageHandler(networkMessage);});
    DiscoverPeers();
    std::cout << "Blockchain client established" << std::endl;
}

void BlockchainClient::MakeTransaction(std::string &receiverId, int amount)
{
    Transaction transaction(this->id, receiverId, amount);

    std::string receiverIp;
    for (const auto& peer : peers) {
        if (peer.first == receiverId) receiverIp = peer.second.first;
    }

    networkClient->sendMessage("0", "8000", "T " + transaction.to_string());
}

void BlockchainClient::DiscoverPeers() {
    std::pair<std::string, std::pair<std::string, std::string>> peer = std::pair<std::string, std::pair<std::string, std::string>>("2", std::pair<std::string, std::string>("2", "1"));
    peers.insert(peer);
    // For now, it's hard-coded - TODO: Add a peer discovery mechanism that works over the network
}

void BlockchainClient::MessageHandler(NetworkMessage &networkMessage)
{
    std::cout << "Blockchain Client nr." << this->id << " received a message " << networkMessage.message << std::endl;
}