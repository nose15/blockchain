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
public:
    NetworkClient(std::string, Network*);
    void sendMessage(std::string, std::string);
    void trafficHandler();
    void disconnect();
};


#endif //BLOCKCHAIN_NETWORKCLIENT_H
