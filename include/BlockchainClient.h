//
// Created by lukasz on 02.12.23.
//

#include <map>
#include <string>

#ifndef BLOCKCHAIN_BLOCKCHAINCLIENT_H
#define BLOCKCHAIN_BLOCKCHAINCLIENT_H


class BlockchainClient {
private:
    std::map<std::string, std::pair<std::string, std::string>> peers;

public:
    BlockchainClient();
    void DiscoverPeers();


};


#endif //BLOCKCHAIN_BLOCKCHAINCLIENT_H
