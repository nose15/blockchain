//
// Created by lukasz on 08.12.23.
//

#include "../../include/Network/PendingRequest.h"

PendingRequest::PendingRequest(unsigned int id, std::future<NetworkMessage> & responseRef, std::promise<NetworkMessage> & responsePromise) : responseRef(responseRef), responsePromise(responsePromise) {
    this->id = id;
    this->status = pending;
}

unsigned int PendingRequest::GetId() { return this->id; }

void PendingRequest::Resolve(const NetworkMessage& value) {
    this->responsePromise.set_value(value);
}
