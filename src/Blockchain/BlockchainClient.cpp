//
// Created by lukasz on 02.12.23.
//

#include <string>
#include "../../include/Blockchain/BlockchainClient.h"
#include <map>

BlockchainClient::BlockchainClient(NetworkClient * networkClient) : networkClient(networkClient)
{
    this->id = networkClient->getIp(); // TODO: More sophisticated id generation
    // TODO: Improve ports flexibility (allow for the ports to be assigned automatically)
    networkClient->AddPortHandler("8000", [this](NetworkMessage &networkMessage) -> NetworkMessage {
        return this->MessageHandler(networkMessage);
    });
    std::cout << "Blockchain client established" << std::endl;
}

void BlockchainClient::MakeTransaction(std::string &receiverId, int amount)
{
    Transaction transaction(this->id, receiverId, amount);
    //TODO: Mechanism that sends the BlockchainTransactionTest to all connected peers
}

NetworkMessage BlockchainClient::MessageHandler(NetworkMessage & networkMessage)
{
    // TODO: Router for endpoints
    std::cout << this->networkClient->getIp() << networkMessage.Body() << std::endl;
    json message = networkMessage.Json();
    std::cout << "Blockchain Client nr." << this->id << " received a message " << message["message"] << std::endl;

    NetworkMessage responseMessage(networkMessage.Id(), Response, networkMessage.ReceiverAddress(), networkMessage.SenderAddress(), R"({"node_id":")" + this->networkClient->getIp() + "\"}");
    return responseMessage;
}

void BlockchainClient::DiscoverPeers(const std::vector<Address>& initialPeers) {
    for (const Address &peerAddress: initialPeers) {
        auto threadFunction = [this, peerAddress]() { this->ConnectPeer(peerAddress); };
        std::thread recursionThread(threadFunction);
        recursionThread.join();

        // TODO: Figure out a way to multiple threads working on different peer chains
    }
}

void BlockchainClient::ConnectPeer(const Address & address)
{
    std::string jsonLiteral = R"({"nodeid": ")" + this->networkClient->getIp() + R"(", "message":"discovery"})";
    NetworkMessage response = networkClient->SendRequest(address, "8000", jsonLiteral);
    json responseJson = response.Json();

    std::string newPeerId = responseJson["node_id"];
    std::cout << this->networkClient->getIp() << " " << newPeerId << std::endl;

//    peers.insert(std::pair<std::string, Address>(newPeerId, address));
//    json peerAddressJson = responseJson["peer"];
//    Address peerAddress = Address(peerAddressJson["ip"], peerAddressJson["port"]);
//
//    if (this->peers.size() < 2) {
//        this->ConnectPeer(peerAddress);
//    }
}
