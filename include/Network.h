//
// Created by lukol on 26.11.2023.
//

#include <string>
#include <map>
#include <iostream>
#include <list>
#include <iostream>
#include <functional>

#ifndef BLOCKCHAIN_NETWORK_H
#define BLOCKCHAIN_NETWORK_H

class Network
{
private:
    std::pair<std::string, std::pair<std::string, std::string>> current_traffic;
    std::map<std::string, std::function<void()>> connected;
    void triggerTraffic();
public:
    Network();
    void sendMessage(const std::string&, const std::string&, const std::string&);
    void connect(std::string, const std::function<void()>&);
};


#endif //BLOCKCHAIN_NETWORK_H
