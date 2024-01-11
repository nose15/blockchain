//
// Created by lukol on 26.11.2023.
//

#include <memory>
#include <Network/Network.hpp>
#include <Blockchain/BlockchainClient.hpp>

#ifndef BLOCKCHAIN_NODE_H
#define BLOCKCHAIN_NODE_H

namespace Node {
	class Node {
	private:
		uint8_t id;
		std::shared_ptr<Network::NetworkClient> networkClient;
		std::unique_ptr<Blockchain::BlockchainClient> blockchainClient;
	public:
		Node(uint8_t id, std::unique_ptr<Network::NetworkSim> network);

		uint8_t getId();

		void Ping(const Address & receiverAddress);

		void RequestTest();

		void BlockchainTest(const std::vector<Address> & initialPeers);

		void BlockchainTransactionTest(uint8_t receiverId, uint32_t amount);
	};
}


#endif //BLOCKCHAIN_NODE_H
