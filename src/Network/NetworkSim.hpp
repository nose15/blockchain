//
// Created by lukol on 26.11.2023.
//

#include <string>
#include <map>
#include <iostream>
#include <list>
#include <functional>
#include <stack>
#include <Network/NetworkMessage.hpp>

#ifndef BLOCKCHAIN_NETWORK_H
#define BLOCKCHAIN_NETWORK_H

namespace Network {
	class NetworkSim {
	private:
		NetworkMessage current_traffic;
		std::map<std::string, std::function<void(NetworkMessage)>> connected;
		std::stack<std::string> availableIps;

		void TriggerReceiver();

		std::string acquireIp();

	public:
		NetworkSim();

		void SendMessage(const NetworkMessage & networkMessage);

		std::string connect(const std::function<void(NetworkMessage)> &);

		void disconnect(const std::string &);
	};
}



#endif //BLOCKCHAIN_NETWORK_H
