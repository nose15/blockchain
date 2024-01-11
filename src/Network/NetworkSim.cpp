//
// Created by lukol on 26.11.2023.
//

#include <Network/NetworkSim.hpp>

namespace Network {
	NetworkSim::NetworkSim() {
		std::cout << "NetworkSim established" << std::endl;
		for (uint8_t i = 255; i > 0; i--) availableIps.push(i);
	}


	uint8_t NetworkSim::acquireIp() {
		if (availableIps.empty()) {
			return 0;
		}

		uint8_t ipAddress = availableIps.top();
		availableIps.pop();

		return ipAddress;
	}


	void NetworkSim::TriggerReceiver() {
		if (current_traffic.ReceiverAddress().ip == 0) {
			for (const auto & connection: connected) {
				connection.second(current_traffic);
			}
			return;
		}

		auto receiver = connected.find(current_traffic.ReceiverAddress().ip);
		if (receiver != connected.end()) {
			std::cout << "" << std::endl;
			receiver->second(current_traffic);
			return;
		}

		throw std::runtime_error("Host not found.");
	}


	void NetworkSim::SendMessage(const NetworkMessage & networkMessage) {
		try {
			this->current_traffic = networkMessage;
			this->TriggerReceiver();
		} catch (std::runtime_error & error) {
			throw std::runtime_error("Message could not be send - " + (std::string) error.what());
		}
	}

	uint8_t NetworkSim::connect(const std::function<void(NetworkMessage)> & handler) {
		try {
			uint8_t ipAddress = this->acquireIp();
			connected.insert({ipAddress, handler});
			return ipAddress;
		} catch (std::runtime_error & error) {
			throw std::runtime_error("Unable to connect - " + (std::string) error.what());
		}
	}

	void NetworkSim::disconnect(uint8_t ipAddress) {
		auto node = connected.find(ipAddress);
		if (node != connected.end()) {
			connected.erase(node);
		}

		availableIps.push(ipAddress);
	}
}
