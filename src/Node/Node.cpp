//
// Created by lukol on 26.11.2023.
//

#include <Node/Node.hpp>
#include <memory>

namespace Node {
	Node::Node(std::string id, std::unique_ptr<Network::NetworkSim> network) : id(std::move(id)) {
		std::cout << "Node " << id << " created" << std::endl;
		this->networkClient = std::make_shared<Network::NetworkClient>(this->id, std::move(network));
		this->blockchainClient = std::make_unique<Blockchain::BlockchainClient>(networkClient);
	}

	std::string Node::getId() {
		return id;
	}


//TODO: Implement some UI
	void Node::Ping(const Address & receiverAddress) {
		Network::NetworkMessage response = networkClient->SendRequest(receiverAddress, "8000", R"({"message": "ping"})");
		json body = response.Json();
		std::cout << this->id << " ping " << receiverAddress.ip << ":" << receiverAddress.port << " => " << body["message"]
		          << std::endl;
	}

	void Node::RequestTest() {
		Network::NetworkMessage response = this->networkClient->SendRequest(Address("2", "8000"), "8000",
		                                                           R"({"message": "request1"})");
	}

	void Node::BlockchainTest(const std::vector<Address> & initialPeers) {
		this->blockchainClient->DiscoverPeers(initialPeers);
	}

	void Node::BlockchainTransactionTest(std::string receiverId, uint32_t amount) {
		blockchainClient->MakeTransaction(receiverId, amount);
	}
}

