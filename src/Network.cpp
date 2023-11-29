//
// Created by lukol on 26.11.2023.
//

#include "../include/Network.h"

Network::Network()
{
    std::cout << "Network established" << std::endl;
}

void Network::sendMessage(const std::string& senderId, const std::string& receiverId, const std::string& message)
{
    std::pair<std::string, std::string> messagePair(senderId, message);
    std::pair<std::string, std::pair<std::string, std::string>> trafficPair(receiverId, messagePair);
    this->current_traffic = trafficPair;
    this->triggerTraffic();
}

void Network::triggerTraffic()
{
    for (const auto& handlerPair : connected) {
        if (current_traffic.first == handlerPair.first)
        {
            handlerPair.second();
        }
    }
}

void Network::connect(std::string nodeId, const std::function<void()>& handler) {
    std::pair<std::string, std::function<void()>> handlerPair(nodeId, handler);
    connected.insert(handlerPair);
}