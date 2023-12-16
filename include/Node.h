//
// Created by lukol on 26.11.2023.
//

#include "Blockchain/BlockchainClient.h"

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
    void Ping(const Address & receiverAddress);
    void transaction(std::string, int);
    void Request();
    void BlockchainTest(const std::vector<Address>& initialPeers);
};

#endif //BLOCKCHAIN_NODE_H
