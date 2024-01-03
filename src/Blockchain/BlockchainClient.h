//
// Created by lukasz on 02.12.23.
//

#include <map>
#include <string>
#include "Transaction.h"
#include "../Network/NetworkClient.h"
#include "../Apps/Router.h"

#ifndef BLOCKCHAIN_BLOCKCHAINCLIENT_H
#define BLOCKCHAIN_BLOCKCHAINCLIENT_H


class BlockchainClient {
private:
    std::map<std::string, Address> peers;
    std::string id;
    NetworkClient * networkClient;
    Router router;
    void ConnectPeer(const Address & address);

    // TODO: Endpoint support for requests
    json DiscoveryEndpoint(NetworkMessage& networkMessage);
public:
    BlockchainClient(NetworkClient*);
    void DiscoverPeers(const std::vector<Address>& initialPeers);
    void MakeTransaction(std::string&, int);
    NetworkMessage MessageHandler(NetworkMessage&);
};


#endif //BLOCKCHAIN_BLOCKCHAINCLIENT_H
