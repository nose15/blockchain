//
// Created by lukasz on 02.12.23.
//

#include <map>
#include <string>
#include "NetworkClient.h"
#include "Transaction.h"

#ifndef BLOCKCHAIN_BLOCKCHAINCLIENT_H
#define BLOCKCHAIN_BLOCKCHAINCLIENT_H


class BlockchainClient {
private:
    std::map<std::string, std::pair<std::string, std::string>> peers;
    std::string id;
    NetworkClient * networkClient;
public:
    BlockchainClient(NetworkClient*);
    void DiscoverPeers();
    void MakeTransaction(std::string&, int);
};


#endif //BLOCKCHAIN_BLOCKCHAINCLIENT_H
