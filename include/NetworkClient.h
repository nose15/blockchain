//
// Created by lukol on 29.11.2023.
//

#include "./Network.h"
#include "./PendingRequest.h"
#include "./Utils.h"
#include <future>

#ifndef BLOCKCHAIN_NETWORKCLIENT_H
#define BLOCKCHAIN_NETWORKCLIENT_H

class NetworkClient {
private:
    std::string nodeId;
    std::string ipAddress;
    std::vector<PendingRequest> m_pendingRequests;

    Network * network;
    std::map<std::string, std::function<void(NetworkMessage&)>> portHandlers;
    NetworkMessage currentResponse;

    void ResponseHandler(const NetworkMessage &);
public:
    NetworkClient(std::string, Network*);
    const std::string& getIp();
    void BroadcastMessage(const std::string &message);
    void MessageHandler(NetworkMessage&);
    void disconnect();
    void addPortHandler(const std::string& port, const std::function<void(NetworkMessage&)>&);
    NetworkMessage SendRequest(const std::string &, const std::string &, const std::string &);
};


#endif //BLOCKCHAIN_NETWORKCLIENT_H
