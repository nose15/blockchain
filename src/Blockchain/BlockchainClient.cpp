//
// Created by lukasz on 02.12.23.
//

#include <string>
#include "../../include/Blockchain/BlockchainClient.h"
#include <map>

BlockchainClient::BlockchainClient(NetworkClient * networkClient) : networkClient(networkClient)
{
    this->id = networkClient->getIp(); // temporary solution - TODO: More sophisticated id generation
    networkClient->addPortHandler("8000", [this](NetworkMessage& networkMessage) -> NetworkMessage { return this->MessageHandler(networkMessage); });
    std::cout << "Blockchain client established" << std::endl;
}


//
//BlockchainClient::BlockchainClient(NetworkClient * networkClient) : networkClient(networkClient) {
//    this->id = networkClient->getIp(); // temporary solution - TODO: More sophisticated id generation
//    networkClient->addPortHandler("8000", [this](NetworkMessage& networkMessage) -> NetworkMessage { return this->MessageHandler(networkMessage);});
//    std::cout << "Blockchain client established" << std::endl;
//}

void BlockchainClient::MakeTransaction(std::string &receiverId, int amount)
{
    Transaction transaction(this->id, receiverId, amount);
    //networkClient->BroadcastMessage("T " + transaction.to_string()); // temporarily it broadcasts - TODO: Send to all peers (allows for multiple port support as peers can have their port specified)
}

NetworkMessage BlockchainClient::MessageHandler(NetworkMessage & networkMessage)
{
    // The purpose of this function will be to route to the desired endpoints (there will be a global collection of
    // endpoint names and their handler functions and this function will route it
    std::cout << this->networkClient->getIp() << networkMessage.Body() << std::endl;
    json body = networkMessage.Json();
    std::cout << "Blockchain Client nr." << this->id << " received a message " << body["message"] << std::endl;

    NetworkMessage responseMessage(networkMessage.Id(), Response, networkMessage.ReceiverAddress(), networkMessage.SenderAddress(), R"({"node_id":")" + this->networkClient->getIp() + "\"}");
    return responseMessage;
}

void BlockchainClient::DiscoverPeers(const std::vector<Address>& initialPeers) {
    for (const Address &peerAddress: initialPeers) {
        auto threadFunction = [this, peerAddress]() { this->ConnectPeer(peerAddress); };
        std::thread recursionThread(threadFunction);
        recursionThread.join();
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

    //    if (this->peers.size() < 2) {
//        this->ConnectPeer(peerAddress);
//    }
}

void BlockchainClient::StartPeerDiscovery(const std::vector<Address>& initialPeers) {
    DiscoverPeers(initialPeers);
}


//void BlockchainClient::ConnectionEndpointHandler(NetworkMessage & networkMessage) {
//    bool connected = false;
//
//    for (const auto& peer : peers) {
//        if (peer.second.first == networkMessage.SenderAddress().ip) {
//            connected = true;
//        }
//    }
//
//    //TODO: Parse a peer ip and send a connection request to it
//}

//void BlockchainClient::PeerRequestEndpointHandler(NetworkMessage & networkMessage)
//{
//
//}
//
//void BlockchainClient::DiscoverPeers() {
//    std::pair<std::string, std::pair<std::string, std::string>> peer = std::pair<std::string, std::pair<std::string, std::string>>("2", std::pair<std::string, std::string>("2", "1"));
//    peers.insert(peer);
//}


