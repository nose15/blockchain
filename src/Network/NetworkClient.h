//
// Created by lukol on 29.11.2023.
//

#include "Network.h"
#include "PendingRequest.h"
#include "../Address.h"
#include "../Utils/Utils.h"
#include <future>

#ifndef BLOCKCHAIN_NETWORKCLIENT_H
#define BLOCKCHAIN_NETWORKCLIENT_H

class NetworkClient {
private:
    std::string nodeId;
    std::string m_ipAddress;
    std::vector<PendingRequest> m_pendingRequests;

    Network * network;
    std::map<std::string, std::function<NetworkMessage(NetworkMessage&)>> portHandlers;
    NetworkMessage currentResponse;

    void RequestHandler(NetworkMessage &);
    void ResponseHandler(NetworkMessage &);
public:
    NetworkClient(std::string, Network*);
    NetworkMessage SendRequest(const Address & receiverAddress, const std::string & responsePort, const std::string &);
    void MessageHandler(NetworkMessage&);
    void BroadcastMessage(const std::string &message);
    void disconnect();

    void AddPortHandler(const std::string& port, const std::function<NetworkMessage(NetworkMessage&)>&);

    const std::string& getIp();
};


#endif //BLOCKCHAIN_NETWORKCLIENT_H
