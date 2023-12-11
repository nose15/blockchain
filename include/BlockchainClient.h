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
    void InitialDiscovery(const std::map<std::string, std::pair<std::string, std::string>>&);
    void ConnectPeer(const std::string&, const Address & address);
    void RequestPeers(const std::string &ip);

    void PeerRequestEndpointHandler(NetworkMessage &);
    void ConnectionEndpointHandler(NetworkMessage &);
public:
    BlockchainClient(NetworkClient*, const std::map<std::string, std::pair<std::string, std::string>>&);
    BlockchainClient(NetworkClient *);
    void DiscoverPeers();
    void DiscoverPeers(const std::map<std::string, std::pair<std::string, std::string>>&);
    void MakeTransaction(std::string&, int);
    NetworkMessage MessageHandler(NetworkMessage&);

};


#endif //BLOCKCHAIN_BLOCKCHAINCLIENT_H
