//
// Created by lukasz on 08.12.23.
//

#include <future>
#include <Network/Network.hpp>
#include <Network/NetworkMessage.hpp>

#ifndef BLOCKCHAIN_PENDINGREQUEST_H
#define BLOCKCHAIN_PENDINGREQUEST_H

namespace Network {
	enum Status {
		pending,
		error,
		resolved,
	};


	class PendingRequest {
	private:
		Status status;
		uint32_t id;
		std::promise<NetworkMessage> & responsePromise;
	public:
		PendingRequest(uint32_t id, std::future<NetworkMessage> & responseFuture,
		               std::promise<NetworkMessage> & responsePromise);

		uint32_t GetId();

		void Resolve(const NetworkMessage & value);
	};
}

#endif //BLOCKCHAIN_PENDINGREQUEST_H
