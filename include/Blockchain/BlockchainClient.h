//
// Created by lukasz on 02.12.23.
//

#include <map>
#include <string>
#include "../Network/NetworkClient.h"
#include "Transaction.h"

#ifndef BLOCKCHAIN_BLOCKCHAINCLIENT_H
#define BLOCKCHAIN_BLOCKCHAINCLIENT_H


class BlockchainClient {
private:
    std::map<std::string, Address> peers;
    std::string id;
    NetworkClient * networkClient;
    void ConnectPeer(const Address & address);

    // TODO: Endpoint support for requests
public:
    BlockchainClient(NetworkClient*);
    void DiscoverPeers(const std::vector<Address>& initialPeers);
    void MakeTransaction(std::string&, int);
    NetworkMessage MessageHandler(NetworkMessage&);
};


#endif //BLOCKCHAIN_BLOCKCHAINCLIENT_H
