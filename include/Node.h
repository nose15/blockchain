//
// Created by lukol on 26.11.2023.
//

#include <string>

#ifndef BLOCKCHAIN_NODE_H
#define BLOCKCHAIN_NODE_H

class Network;

class Node
{
private:
    std::string m_id;
    Network * network;
public:
    Node(std::string);
    void triggerReceive(std::string);
    void ping(std::string);
    void setNetwork(Network& network);
    std::string getId();
};

#endif //BLOCKCHAIN_NODE_H
