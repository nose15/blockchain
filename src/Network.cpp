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
    if (current_traffic.receiverIp == "0")
    {
        for (const auto& connection : connected)
        {
            connection.second(current_traffic);
        }
    }

    for (const auto& connection : connected)
    {
        if (current_traffic.receiverIp == connection.first)
        {
            connection.second(current_traffic);
        }
    }
}


void Network::sendMessage(const std::string& senderIp, const std::string& receiverIp, const std::string& message)
{
    NetworkMessage traffic(senderIp, receiverIp, message);
    this->current_traffic = traffic;
    this->triggerTraffic();
}


std::string Network::connect(const std::function<void(NetworkMessage)>& handler) {
    std::string ipAddress = this->acquireIp();
    std::pair<std::string, std::function<void(NetworkMessage)>> handlerPair(ipAddress, handler);
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