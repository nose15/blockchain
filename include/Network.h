//
// Created by lukol on 26.11.2023.
//

#include <string>
#include <map>
#include <iostream>
#include <list>
#include <iostream>
#include <functional>
#include <stack>
#include "NetworkMessage.h"

#ifndef BLOCKCHAIN_NETWORK_H
#define BLOCKCHAIN_NETWORK_H

class Network
{
private:
    NetworkMessage current_traffic;
    std::map<std::string, std::function<void()>> connected;
    std::stack<std::string> availableIps;

    void triggerTraffic();
    std::string acquireIp();
public:
    Network();
    void sendMessage(const std::string&, const std::string&, const std::string&);
    std::string connect(const std::function<void()>&);
    void disconnect(const std::string&);
};


#endif //BLOCKCHAIN_NETWORK_H
