//
// Created by lukol on 29.11.2023.
//

#include <iostream>
#include <string>

#include "../include/NetworkClient.h"


NetworkClient::NetworkClient(std::string nodeId, Network * network) : nodeId(nodeId), network(network)
{
    this->ipAddress = network->connect([this](NetworkMessage networkMessage) {this->trafficHandler(networkMessage);});
    std::cout << "NetworkClient for " << this->nodeId << " established" << std::endl;
}

void NetworkClient::sendMessage(std::string receiverIp, std::string port, std::string message)
{
    network->sendMessage(this->ipAddress, receiverIp, port, message);
}

void NetworkClient::trafficHandler(NetworkMessage& networkMessage)
{
    auto iter = portHandlers.find(networkMessage.port);
    if (iter == portHandlers.end())
    {
        std::cout << this->nodeId << " Received a message but to invalid port" << std::endl;
        return;
    }
    iter->second(networkMessage);
}

void NetworkClient::disconnect() {
    this->network->disconnect(this->ipAddress);
    this->network = nullptr;
}

const std::string& NetworkClient::getIp() {
    return this->ipAddress;
}

void NetworkClient::addPortHandler(std::string port, std::function<void(NetworkMessage&)> handler)
{
    auto iter = portHandlers.find(port);
    if (iter != portHandlers.end()) throw std::runtime_error("This port is already occupied"); // TODO: Add custom errors

    std::pair<std::string, std::function<void(NetworkMessage&)>> handlerPair(port, handler);

    portHandlers.insert(handlerPair);
}
