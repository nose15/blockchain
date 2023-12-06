//
// Created by lukol on 29.11.2023.
//

#include <iostream>
#include <string>
#include <utility>

#include "../include/NetworkClient.h"


NetworkClient::NetworkClient(std::string nodeId, Network * network) : nodeId(std::move(nodeId)), network(network)
{
    this->ipAddress = network->connect([this](NetworkMessage networkMessage) {this->trafficHandler(networkMessage);});
    std::cout << "NetworkClient for " << this->nodeId << " established" << std::endl;
}

void NetworkClient::SendMessage(const std::string& receiverIp, const std::string& port, const std::string& message)
{
    network->sendMessage(this->ipAddress, receiverIp, port, message);
}

void NetworkClient::BroadcastMessage(const std::string& message)
{
    network->sendMessage(this->ipAddress, "0", message);
}

void NetworkClient::trafficHandler(NetworkMessage& networkMessage)
{
    if (networkMessage.receiverIp=="0" && networkMessage.port.empty()) {
        std::cout << this->nodeId << " received a broadcasted message" << std::endl;
        return;
    }

    auto node = portHandlers.find(networkMessage.port);
    if (node == portHandlers.end())
    {
        std::cout << this->nodeId << " Received a message but to invalid port" << std::endl;
        return;
    }
    node->second(networkMessage);
}

void NetworkClient::disconnect() {
    this->network->disconnect(this->ipAddress);
    this->network = nullptr;
} // TODO: Connect method, so the client can be reused


void NetworkClient::addPortHandler(const std::string& port, const std::function<void(NetworkMessage&)>& handler)
{
    auto iter = portHandlers.find(port);
    if (iter != portHandlers.end()) throw std::runtime_error("This port is already occupied"); // TODO: Add custom errors

    std::pair<std::string, std::function<void(NetworkMessage&)>> handlerPair(port, handler);

    portHandlers.insert(handlerPair);
}


const std::string& NetworkClient::getIp() { return this->ipAddress; }

