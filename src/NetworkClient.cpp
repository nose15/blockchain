//
// Created by lukol on 29.11.2023.
//

#include <iostream>
#include <string>

#include "../include/NetworkClient.h"


NetworkClient::NetworkClient(std::string nodeId, Network * network) : nodeId(nodeId), network(network)
{
    network->connect(this->nodeId, [this] { trafficHandler(); });
    std::cout << "NetworkClient for " << this->nodeId << " established" << std::endl;
}

void NetworkClient::sendMessage(std::string receiverId, std::string message)
{
    network->sendMessage(this->nodeId, receiverId, message);
}

void NetworkClient::trafficHandler()
{
    std::cout << this->nodeId << " received a message" << std::endl;
}

