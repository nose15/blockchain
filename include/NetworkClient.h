//
// Created by lukol on 29.11.2023.
//

#include "Network.h"
#include <future>

#ifndef BLOCKCHAIN_NETWORKCLIENT_H
#define BLOCKCHAIN_NETWORKCLIENT_H

class NetworkClient {
private:
    std::string nodeId;
    std::string ipAddress;
    Network * network;
    std::map<std::string, std::function<void(NetworkMessage&)>> portHandlers;
    NetworkMessage currentResponse;
public:
    NetworkClient(std::string, Network*);
    const std::string& getIp();
    void SendMessage(const std::string &receiverIp, const std::string &port, const std::string &message);
    void BroadcastMessage(const std::string &message);
    void MessageHandler(NetworkMessage&);
    void disconnect();
    void addPortHandler(const std::string& port, const std::function<void(NetworkMessage&)>&);
    std::future<NetworkMessage> Request(const std::string &receiverIp, const std::string &port, const std::string &message);
};


#endif //BLOCKCHAIN_NETWORKCLIENT_H
