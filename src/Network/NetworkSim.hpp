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
		std::map<uint8_t, std::function<void(NetworkMessage)>> connected;
		std::stack<uint8_t> availableIps;

		void TriggerReceiver();

		uint8_t acquireIp();

	public:
		NetworkSim();

		void SendMessage(const NetworkMessage & networkMessage);

		uint8_t connect(const std::function<void(NetworkMessage)> &);

		void disconnect(uint8_t);
	};
}



#endif //BLOCKCHAIN_NETWORK_H
