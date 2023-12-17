//
// Created by lukol on 26.11.2023.
//

#include "../../include/Network/Network.h"

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


void Network::TriggerReceiver()
{
    if (current_traffic.ReceiverAddress().ip == "0")
    {
        for (const auto& connection : connected)
        {
            connection.second(current_traffic);
        }

        return;
    }

    auto receiver = connected.find(current_traffic.ReceiverAddress().ip);
    if (receiver != connected.end())
    {
        std::cout << "" << std::endl;
        receiver->second(current_traffic);

    }
}


void Network::SendMessage(const NetworkMessage & networkMessage)
{
    this->current_traffic = networkMessage;
    this->TriggerReceiver();
}

std::string Network::connect(const std::function<void(NetworkMessage)>& handler) {
    std::string ipAddress = this->acquireIp();
    std::pair<std::string, std::function<void(NetworkMessage)>> handlerPair(ipAddress, handler);
    connected.insert(handlerPair);
    return ipAddress;
}

void Network::disconnect(const std::string &ipAddress)
{
    auto node = connected.find(ipAddress);
    if (node != connected.end()) {
        connected.erase(node);
    }

    availableIps.push(ipAddress);
}