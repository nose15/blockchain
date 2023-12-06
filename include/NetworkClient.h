//
// Created by lukol on 29.11.2023.
//

#include "Network.h"

#ifndef BLOCKCHAIN_NETWORKCLIENT_H
#define BLOCKCHAIN_NETWORKCLIENT_H

class NetworkClient {
private:
    std::string nodeId;
    std::string ipAddress;
    Network * network;
    std::map<std::string, std::function<void(NetworkMessage&)>> portHandlers;
public:
    NetworkClient(std::string, Network*);
    const std::string& getIp();
    void SendMessage(const std::string &receiverIp, const std::string &port, const std::string &message);
    void BroadcastMessage(const std::string &message);
    void trafficHandler(NetworkMessage&);
    void disconnect();
    void addPortHandler(const std::string& port, const std::function<void(NetworkMessage&)>&);

};


#endif //BLOCKCHAIN_NETWORKCLIENT_H
