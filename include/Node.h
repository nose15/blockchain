//
// Created by lukol on 26.11.2023.
//

#include "NetworkClient.h"

#ifndef BLOCKCHAIN_NODE_H
#define BLOCKCHAIN_NODE_H

class Node
{
private:
    std::string m_id;
    NetworkClient * networkClient;
public:
    Node(std::string, Network * network);
    std::string getId();
    void ping(std::string);
};

#endif //BLOCKCHAIN_NODE_H
