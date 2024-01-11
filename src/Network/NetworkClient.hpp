//
// Created by lukol on 29.11.2023.
//

#include <iostream>
#include <string>
#include <utility>
#include <future>
#include <memory>
#include <Network/NetworkSim.hpp>
#include <Network/NetworkMessage.hpp>
#include <Network/PendingRequest.hpp>
#include <Utils/Utils.hpp>

#ifndef BLOCKCHAIN_NETWORKCLIENT_H
#define BLOCKCHAIN_NETWORKCLIENT_H

namespace Network {
	class NetworkClient {
	protected:
		uint8_t nodeId;
		uint8_t ipAddress;
		std::vector<PendingRequest> pendingRequests;

		std::unique_ptr<NetworkSim> network;
		std::map<uint16_t, std::function<NetworkMessage(NetworkMessage &)>> portHandlers;
		NetworkMessage currentResponse;

		NetworkMessage && RequestHandler(NetworkMessage &);

		void ResponseHandler(NetworkMessage &);

	public:
		NetworkClient(uint8_t nodeId, std::unique_ptr<NetworkSim> networkSim);

		void AddPortHandler(uint16_t port, const std::function<NetworkMessage(NetworkMessage &)> &);

		void MessageHandler(NetworkMessage &);

		NetworkMessage SendRequest(const Address & receiverAddress, uint16_t responsePort, const std::string &);

		void BroadcastMessage(const std::string & message);

		void disconnect();

		uint8_t getIp();
	};
}



#endif //BLOCKCHAIN_NETWORKCLIENT_H
