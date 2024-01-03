//
// Created by lukasz on 08.12.23.
//

#include <future>
#include "NetworkMessage.h"

#ifndef BLOCKCHAIN_PENDINGREQUEST_H
#define BLOCKCHAIN_PENDINGREQUEST_H

enum Status {
    pending,
    error,
    resolved,
};


class PendingRequest {
private:
    Status status;
    unsigned int id;
    std::future<NetworkMessage> & responseRef;
    std::promise<NetworkMessage> & responsePromise;
public:
    PendingRequest(unsigned int id, std::future<NetworkMessage> & responseFuture, std::promise<NetworkMessage> & responsePromise);
    unsigned int GetId();
    void Resolve(const NetworkMessage& value);
};

#endif //BLOCKCHAIN_PENDINGREQUEST_H
