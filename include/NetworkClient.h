//
// Created by lukol on 29.11.2023.
//

#include "Network.h"

#ifndef BLOCKCHAIN_NETWORKCLIENT_H
#define BLOCKCHAIN_NETWORKCLIENT_H

class NetworkClient {
private:
    std::string nodeId;
    Network * network;
public:
    NetworkClient(std::string, Network*);
    void sendMessage(std::string, std::string);
    void trafficHandler();
};


#endif //BLOCKCHAIN_NETWORKCLIENT_H
