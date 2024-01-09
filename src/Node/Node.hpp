//
// Created by lukol on 26.11.2023.
//

#include <Blockchain/BlockchainClient.hpp>

#ifndef BLOCKCHAIN_NODE_H
#define BLOCKCHAIN_NODE_H

class Node {
private:
	std::string id;
	NetworkClient *networkClient;
	BlockchainClient *blockchainClient;
public:
	Node(std::string, Network *network);

	std::string getId();

	void Ping(const Address & receiverAddress);

	void RequestTest();

	void BlockchainTest(const std::vector<Address> & initialPeers);

	void BlockchainTransactionTest(std::string receiverId, uint32_t amount);
};

#endif //BLOCKCHAIN_NODE_H
