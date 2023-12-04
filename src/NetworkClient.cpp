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

void NetworkClient::sendMessage(std::string receiverIp, std::string message)
{
    network->sendMessage(this->ipAddress, receiverIp, message);
}

void NetworkClient::trafficHandler(const NetworkMessage& networkMessage)
{
    std::cout << this->nodeId << " received a message: " << networkMessage.message << std::endl;
}

void NetworkClient::disconnect() {
    this->network->disconnect(this->ipAddress);
    this->network = nullptr;
}

const std::string& NetworkClient::getIp() {
    return this->ipAddress;
}