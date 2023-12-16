//
// Created by lukol on 29.11.2023.
//

#include <iostream>
#include <string>
#include <utility>

#include "../../include/Network/NetworkClient.h"


NetworkClient::NetworkClient(std::string nodeId, Network * network) : nodeId(std::move(nodeId)), network(network)
{
    this->m_ipAddress = network->connect([this](NetworkMessage networkMessage) { this->MessageHandler(networkMessage);});
    std::cout << "NetworkClient for " << this->nodeId << " established" << std::endl;
}

void NetworkClient::BroadcastMessage(const std::string& message)
{
    //TODO: Add NetworkMessageFactory
    unsigned int id = Utils::generateRandomId();
    NetworkMessage networkMessage(id, Broadcast, Address(m_ipAddress, "0"), Address("0", "0"), message);
    network->SendMessage(networkMessage);
}

void NetworkClient::MessageHandler(NetworkMessage& networkMessage)
{


    switch (networkMessage.Type()) {
        case Response: {
            ResponseHandler(networkMessage);
            break;
        }
        case Request: {
            std::string port = networkMessage.SenderAddress().port;
            try {
                std::function<NetworkMessage(NetworkMessage &)> portHandler = portHandlers[port];
                NetworkMessage response = portHandler(networkMessage);
                network->SendMessage(response);
            } catch (const std::bad_function_call & e) {
                std::cout << "func doesnt exist for " << port << std::endl;
            }
            break;
        }
        case Broadcast: {
            std::cout << this->nodeId << " received a broadcasted message" << std::endl;
            break;
        }
        case Ping: {
            std::string port = networkMessage.SenderAddress().port;
            NetworkMessage responseMessage(networkMessage.Id(), Response, Address(m_ipAddress, port), networkMessage.SenderAddress(), "{}");
            break;
        }
        default: {
            break;
        }
    }

    auto node = portHandlers.find(networkMessage.SenderAddress().port);
    if (node == portHandlers.end())
    {
        return;
    }

    node->second(networkMessage);
}

void NetworkClient::disconnect() {
    this->network->disconnect(this->m_ipAddress);
    this->network = nullptr;
} // TODO: Connect method, so the client can be reused


void NetworkClient::addPortHandler(const std::string& port, const std::function<NetworkMessage(NetworkMessage&)>& handler)
{
    auto iter = portHandlers.find(port);
    if (iter != portHandlers.end()) throw std::runtime_error("This port is already occupied"); // TODO: Add custom errors

    std::pair<std::string, std::function<NetworkMessage(NetworkMessage&)>> handlerPair(port, handler);

    portHandlers.insert(handlerPair);
}


const std::string& NetworkClient::getIp() { return this->m_ipAddress; }


NetworkMessage NetworkClient::SendRequest(const Address & receiverAddress, const std::string & responsePort, const std::string &message)
{
    std::promise<NetworkMessage> pendingResponse;
    std::future<NetworkMessage> responseFuture = pendingResponse.get_future();
    unsigned int requestId = Utils::generateRandomId();

    PendingRequest pendingRequest(requestId, responseFuture, pendingResponse);
    m_pendingRequests.push_back(pendingRequest);

    NetworkMessage networkMessage(requestId, Request, Address(m_ipAddress, responsePort), receiverAddress, message);
    this->network->SendMessage(networkMessage);
    NetworkMessage response = responseFuture.get();

    return response;
}

void NetworkClient::ResponseHandler(NetworkMessage & networkMessage)
{
    if (networkMessage.Type() != Response)
    {
        return;
    }

    for (auto pendingRequest : this->m_pendingRequests)
    {
        if (pendingRequest.GetId() == networkMessage.Id())
        {
            pendingRequest.Resolve(networkMessage);
        }
    }
}






