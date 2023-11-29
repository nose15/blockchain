//
// Created by lukol on 26.11.2023.
//

#include <string>
#include <map>
#include <iostream>

#include "Node.h"

#ifndef BLOCKCHAIN_NETWORK_H
#define BLOCKCHAIN_NETWORK_H

class Network
{
private:
    std::map<std::string, Node&> m_nodes;
public:
    Network();
    void add_node(const std::string&, Node&);
    void send(std::string, std::string, std::string);
};


#endif //BLOCKCHAIN_NETWORK_H
