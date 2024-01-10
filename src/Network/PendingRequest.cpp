//
// Created by lukasz on 08.12.23.
//

#include <Network/PendingRequest.hpp>

namespace Network {
	PendingRequest::PendingRequest(uint32_t id, std::future<NetworkMessage> & responseRef,
	                               std::promise<NetworkMessage> & responsePromise) : responsePromise(responsePromise) {
		this->id = id;
		this->status = pending;
	}

	uint32_t PendingRequest::GetId() { return this->id; }

	void PendingRequest::Resolve(const NetworkMessage & value) {
		this->responsePromise.set_value(value);
	}
}

