//
// Created by lukol on 26.11.2023.
//

#include "../include/Network.h"

Network::Network()
{
    std::cout << "Network established" << std::endl;
    for (int i = 255; i > 0; i--) availableIps.push(std::to_string(i));
}


std::string Network::acquireIp()
{
    std::string ipAddress = availableIps.top();
    availableIps.pop();

    return ipAddress;
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


void Network::sendMessage(const std::string& senderIp, const std::string& receiverIp, const std::string& message)
{
    std::pair<std::string, std::string> messagePair(senderIp, message);
    std::pair<std::string, std::pair<std::string, std::string>> trafficPair(receiverIp, messagePair);
    this->current_traffic = trafficPair;
    this->triggerTraffic();
}


std::string Network::connect(const std::function<void()>& handler) {
    std::string ipAddress = this->acquireIp();
    std::pair<std::string, std::function<void()>> handlerPair(ipAddress, handler);
    connected.insert(handlerPair);
    return ipAddress;
}

void Network::disconnect(const std::string &ipAddress)
{
    auto mapEntry = connected.find(ipAddress);
    if (mapEntry != connected.end()) {
        connected.erase(mapEntry);
    }

    availableIps.push(ipAddress);
}