//
// Created by lukol on 29.11.2023.
//

#include <iostream>
#include <string>
#include <utility>

#include "NetworkClient.h"


NetworkClient::NetworkClient(std::string nodeId, Network * network) : nodeId(std::move(nodeId)), network(network)
{
    this->ipAddress = network->connect([this](NetworkMessage networkMessage) { this->MessageHandler(networkMessage);});
    std::cout << "NetworkClient for " << this->nodeId << " established" << std::endl;
}

NetworkMessage NetworkClient::SendRequest(const Address & receiverAddress, const std::string & responsePort, const std::string &message)
{
    std::promise<NetworkMessage> pendingResponse;
    std::future<NetworkMessage> responseFuture = pendingResponse.get_future();
    unsigned int requestId = Utils::generateRandomId();

    PendingRequest pendingRequest(requestId, responseFuture, pendingResponse);
    pendingRequests.push_back(pendingRequest);

    NetworkMessage networkMessage(requestId, Request, Address(ipAddress, responsePort), receiverAddress, message);
    this->network->SendMessage(networkMessage);
    NetworkMessage response = responseFuture.get();

    return response;
}

// Probably will have to invert the handling process. First handle the port and then the message type
void NetworkClient::MessageHandler(NetworkMessage& networkMessage)
{
    switch (networkMessage.Type()) {
        case Response: {
            ResponseHandler(networkMessage);
            break;
        }
        case Request: {
            RequestHandler(networkMessage);
            break;
        }
        case Broadcast: {
            std::cout << this->nodeId << " received a broadcasted message" << std::endl;
            break;
        }
        default: {
            break;
        }
    }
}

void NetworkClient::RequestHandler(NetworkMessage & networkMessage) {
    if (networkMessage.Type() != Request) {
        throw std::runtime_error("Invalid message type - should be \"Request\"");
    }

    std::string port = networkMessage.SenderAddress().port;

    try {
        std::function<NetworkMessage(NetworkMessage &)> portHandler = portHandlers[port];
        NetworkMessage response = portHandler(networkMessage);
        network->SendMessage(response);
    } catch (const std::bad_function_call & e) {
        throw std::runtime_error("The port " + port + " doesn't have a handler");
    }
}


void NetworkClient::ResponseHandler(NetworkMessage & networkMessage)
{
    if (networkMessage.Type() != Response)
    {
        throw std::runtime_error("Invalid message type - should be \"Response\"");
    }

    for (auto pendingRequest : this->pendingRequests)
    {
        if (pendingRequest.GetId() == networkMessage.Id())
        {
            pendingRequest.Resolve(networkMessage);
            break;
        }
    }
}

void NetworkClient::AddPortHandler(const std::string& port, const std::function<NetworkMessage(NetworkMessage&)>& handler)
{
    auto iter = portHandlers.find(port);
    if (iter != portHandlers.end()) throw std::runtime_error("This port is already occupied");

    std::pair<std::string, std::function<NetworkMessage(NetworkMessage&)>> handlerPair(port, handler);

    portHandlers.insert(handlerPair);
}

void NetworkClient::BroadcastMessage(const std::string& message)
{
    //TODO: Add NetworkMessageFactory
    unsigned int id = Utils::generateRandomId();
    NetworkMessage networkMessage(id, Broadcast, Address(ipAddress, "0"), Address("0", "0"), message);
    network->SendMessage(networkMessage);
}

void NetworkClient::disconnect() {
    this->network->disconnect(this->ipAddress);
    this->network = nullptr;
} // TODO: Connect method, so the client can be reused


const std::string& NetworkClient::getIp() { return this->ipAddress; }







