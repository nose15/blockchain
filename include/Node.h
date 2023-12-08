//
// Created by lukol on 26.11.2023.
//

#include "BlockchainClient.h"

#ifndef BLOCKCHAIN_NODE_H
#define BLOCKCHAIN_NODE_H

class Node
{
private:
    std::string m_id;
    NetworkClient * networkClient;
    BlockchainClient * blockchainClient;
public:
    Node(std::string, Network * network);
    std::string getId();
    void ping(const std::string&);
    void transaction(std::string, int);
    void Request();
};

#endif //BLOCKCHAIN_NODE_H
