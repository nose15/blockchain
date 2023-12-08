//
// Created by lukasz on 02.12.23.
//

#include <string>
#include "../include/BlockchainClient.h"
#include <map>

BlockchainClient::BlockchainClient(NetworkClient * networkClient, const std::map<std::string, std::pair<std::string, std::string>>& initialPeers) : networkClient(networkClient)
{
    this->id = networkClient->getIp(); // temporary solution - TODO: More sophisticated id generation
    networkClient->addPortHandler("8000", [this](NetworkMessage& networkMessage) {this->MessageHandler(networkMessage);});
    DiscoverPeers();
    std::cout << "Blockchain client established" << std::endl;
}

void BlockchainClient::MakeTransaction(std::string &receiverId, int amount)
{
    Transaction transaction(this->id, receiverId, amount);
    networkClient->BroadcastMessage("T " + transaction.to_string()); // temporarily it broadcasts - TODO: Send to all peers (allows for multiple port support as peers can have their port specified)
}

void BlockchainClient::MessageHandler(NetworkMessage &networkMessage)
{
    // The purpose of this function will be to route to the desired endpoints (there will be a global collection of
    // endpoint names and their handler functions and this function will route it

    std::cout << "Blockchain Client nr." << this->id << " received a message " << networkMessage.message << std::endl;
}

void BlockchainClient::DiscoverPeers(const std::map<std::string, std::pair<std::string, std::string>>& peerMap) {

    std::pair<std::string, std::pair<std::string, std::string>> peer = std::pair<std::string, std::pair<std::string, std::string>>("2", std::pair<std::string, std::string>("2", "1"));
    peers.insert(peer);
    // For now, it's hard-coded - TODO: Add a peer discovery mechanism that works over the network
}

void BlockchainClient::InitialDiscovery(const std::map<std::string, std::pair<std::string, std::string>> & initialPeers)
{
    // connect with all the initial peers
    // the initial peers should return their randomly selected peers and those peers should also return some peers
    // this should repeat to the depth of x
    // the object keeps receiving new peers until it has y of them

    // This function requests random peer ips from the peers
    // Then it takes those ips and requests another set of ips
    // It repeats the cycle until it has x peers

    // The handler function that answers the connect function should return up to x random peers from its peer base
    // This way we are sure that at least some of those peers are unknown to the Node

    // TODO: Need to implement routing system for the blockchain client, so it's easy to implement endpoints and to
    // serialize data into JSONs
}

void BlockchainClient::ConnectPeer(std::string peerId, const std::pair<std::string, std::string> &address)
{
    // It sends the connection request to the peer
    // If the peer responds with true then
    // Request other peers from the peer
}

void BlockchainClient::RequestPeers(const std::string& ip) {

}

void BlockchainClient::ConnectionEndpointHandler(NetworkMessage & networkMessage) {
    // TODO: Check if it's right (probably isnt)
    bool connected = false;

    for (const auto& peer : peers) {
        if (peer.second.first == networkMessage.senderIp) {
            connected = true;
        }
    }

    if (!connected) {
        ConnectPeer(networkMessage.senderIp, std::pair<std::string, std::string>(networkMessage.senderIp, networkMessage.port));
    }
}

void BlockchainClient::PeerRequestEndpointHandler(NetworkMessage & networkMessage)
{

}
