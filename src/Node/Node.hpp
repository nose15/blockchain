//
// Created by lukol on 26.11.2023.
//

#include <Blockchain/BlockchainClient.hpp>

#ifndef BLOCKCHAIN_NODE_H
#define BLOCKCHAIN_NODE_H

namespace Node {
	class Node {
	private:
		std::string id;
		Network::NetworkClient * networkClient;
		Blockchain::BlockchainClient * blockchainClient;
	public:
		Node(std::string, Network::NetworkSim * network);

		std::string getId();

		void Ping(const Address & receiverAddress);

		void RequestTest();

		void BlockchainTest(const std::vector<Address> & initialPeers);

		void BlockchainTransactionTest(std::string receiverId, uint32_t amount);
	};
}


#endif //BLOCKCHAIN_NODE_H
