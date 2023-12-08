//
// Created by lukol on 29.11.2023.
//

#include <iostream>
#include <string>
#include <utility>

#include "../include/NetworkClient.h"


NetworkClient::NetworkClient(std::string nodeId, Network * network) : nodeId(std::move(nodeId)), network(network)
{
    this->ipAddress = network->connect([this](NetworkMessage networkMessage) { this->MessageHandler(networkMessage);});
    std::cout << "NetworkClient for " << this->nodeId << " established" << std::endl;
}

void NetworkClient::BroadcastMessage(const std::string& message)
{
    //TODO: Add NetworkMessageFactory
    unsigned int id = Utils::generateRandomId();
    NetworkMessage networkMessage(this->ipAddress, "0", message, "", id, Broadcast);
    network->SendMessage(networkMessage);
}

void NetworkClient::MessageHandler(NetworkMessage& networkMessage)
{
    //TODO: Once ports are working, make it a proper message handler and pull out the request, response etc. handlers
    switch (networkMessage.m_messageType) {
        case Response: {
            ResponseHandler(networkMessage);
            break;
        }
        case Request: {
            NetworkMessage responseMessage(this->ipAddress, networkMessage.senderIp, "RR it works", "0", networkMessage.id, Response);
            this->network->SendMessage(responseMessage);
            break;
        }
        case Broadcast: {
            std::cout << this->nodeId << " received a broadcasted message" << std::endl;
            break;
        }
        case Ping: {
            NetworkMessage responseMessage(this->ipAddress, networkMessage.senderIp, "pong", "0", networkMessage.id, Response);
            break;
        }
        default: {
            break;
        }
    }

    auto node = portHandlers.find(networkMessage.port);
    if (node == portHandlers.end())
    {
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


NetworkMessage NetworkClient::SendRequest(const std::string &receiverIp, const std::string &port, const std::string &message)
{
    std::promise<NetworkMessage> pendingResponse;
    std::future<NetworkMessage> responseFuture = pendingResponse.get_future();
    unsigned int requestId = Utils::generateRandomId();

    PendingRequest pendingRequest(requestId, responseFuture, pendingResponse);
    m_pendingRequests.push_back(pendingRequest);

    NetworkMessage networkMessage(this->ipAddress, receiverIp, message, port, requestId, Request);
    this->network->SendMessage(networkMessage);
    NetworkMessage response = responseFuture.get();

    return response;
}

void NetworkClient::ResponseHandler(const NetworkMessage & networkMessage)
{
    if (networkMessage.m_messageType != Response)
    {
        return;
    }

    for (auto pendingRequest : this->m_pendingRequests)
    {
        if (pendingRequest.GetId() == networkMessage.id)
        {
            pendingRequest.Resolve(networkMessage);
        }
    }
}






