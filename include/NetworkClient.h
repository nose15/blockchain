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
    void sendMessage(std::string, std::string, std::string);
    void trafficHandler(NetworkMessage&);
    void disconnect();
    void addPortHandler(std::string port, std::function<void(NetworkMessage&)>);
};


#endif //BLOCKCHAIN_NETWORKCLIENT_H
