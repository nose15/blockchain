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
    void InitialDiscovery(const std::string&);
    void ConnectPeer(const Address & address);
    void RequestPeers(const std::string &ip);

    void PeerRequestEndpointHandler(NetworkMessage &);
    void ConnectionEndpointHandler(NetworkMessage &);
public:
    BlockchainClient(NetworkClient*);
//    BlockchainClient(NetworkClient *);
    void StartPeerDiscovery(const std::vector<Address>& initialPeers);
    void DiscoverPeers(const std::vector<Address>& initialPeers);
    void MakeTransaction(std::string&, int);
    NetworkMessage MessageHandler(NetworkMessage&);

};


#endif //BLOCKCHAIN_BLOCKCHAINCLIENT_H
