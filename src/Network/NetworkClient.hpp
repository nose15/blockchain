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
		std::string nodeId;
		std::string ipAddress;
		std::vector<PendingRequest> pendingRequests;

		std::unique_ptr<NetworkSim> network;
		std::map<std::string, std::function<NetworkMessage(NetworkMessage &)>> portHandlers;
		NetworkMessage currentResponse;

		NetworkMessage && RequestHandler(NetworkMessage &);

		void ResponseHandler(NetworkMessage &);

	public:
		NetworkClient(std::string, std::unique_ptr<NetworkSim>);

		void AddPortHandler(const std::string & port, const std::function<NetworkMessage(NetworkMessage &)> &);

		void MessageHandler(NetworkMessage &);

		NetworkMessage SendRequest(const Address & receiverAddress, const std::string & responsePort, const std::string &);

		void BroadcastMessage(const std::string & message);

		void disconnect();

		const std::string & getIp();
	};
}



#endif //BLOCKCHAIN_NETWORKCLIENT_H
