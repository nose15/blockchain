//
// Created by lukasz on 02.12.23.
//

#include <Blockchain/BlockchainClient.hpp>
#include "DataParser/DataParser.hpp"

BlockchainClient::BlockchainClient(NetworkClient *networkClient) : networkClient(networkClient) {
	// TODO: More sophisticated id generation
	// TODO: Improve ports flexibility (allow for the ports to be assigned automatically)

	this->id = networkClient->getIp();

	networkClient->AddPortHandler("8000", [this](NetworkMessage & networkMessage) -> NetworkMessage {
		return this->MessageHandler(networkMessage);
	});

	router.AddEndpoint("/discovery", [this](NetworkMessage & networkMessage) -> json {
		return this->DiscoveryEndpoint(networkMessage);
	});
	router.AddEndpoint("/connect", [this](NetworkMessage & networkMessage) -> json {
		return this->ConnectEndpoint(networkMessage);
	});

	std::cout << "Blockchain client established" << std::endl;
}

void BlockchainClient::MakeTransaction(std::string & receiverId, uint32_t amount) {
	Transaction transaction(this->id, receiverId, amount);
	//TODO: Mechanism that sends the BlockchainTransactionTest to all connected peers
}

NetworkMessage BlockchainClient::MessageHandler(NetworkMessage & networkMessage) {
	std::function<json(NetworkMessage &)> endpointHandler = router.Dispatch(networkMessage.Body());
	json responseBody = endpointHandler(networkMessage);

	std::string responseBodyStr = "200 OK " + responseBody.dump();

	NetworkMessage responseMessage(networkMessage.Id(), Response, networkMessage.ReceiverAddress(),
	                               networkMessage.SenderAddress(), responseBodyStr);
	return responseMessage;
}

void BlockchainClient::DiscoverPeers(const std::vector<Address> & initialPeers) {
	for (const Address & peerAddress: initialPeers) {
		std::cout << "Blockchain Client " << this->id << " sent a message ";
		NetworkMessage response = networkClient->SendRequest(peerAddress, "8000",
		                                                     R"(GET /connect {"node_id":")" + this->id + "\"}");
		std::cout << response.Body() << std::endl;
		if (DataParser::FetchMethod(response.Body()) == "200") {
			std::string peerId = json::parse(DataParser::FetchContent(response.Body()))["node_id"];
			if (peers[peerId].ip != peerAddress.ip) {
				peers[peerId] = peerAddress;
			}

			NetworkMessage discoveryResponse = networkClient->SendRequest(peerAddress, "8000",
			                                                              R"(GET /discovery {"node_id":")" + this->id +
			                                                              "\"}");
			std::cout << discoveryResponse.Body() << std::endl;
		}
		Utils::PrintMap(peers);
	}
}

json BlockchainClient::DiscoveryEndpoint(NetworkMessage & networkMessage) {
	std::string method = DataParser::FetchMethod(networkMessage.Body());
	std::cout << "Blockchain Client " << this->id << "/discovery received a " << method << " message " << std::endl;
	std::string contentStr = DataParser::FetchContent(networkMessage.Body());
	json content = json::parse(contentStr);
	json responseMessage;
	responseMessage["peers"] = {};
	for (const auto & peer: peers) {
		responseMessage["peers"].push_back({peer.second.ip, peer.second.port});
	}

	responseMessage["node_id"] = this->id;

	return responseMessage;
}

json BlockchainClient::ConnectEndpoint(NetworkMessage & networkMessage) {
	std::string method = DataParser::FetchMethod(networkMessage.Body());
	std::cout << "Blockchain Client " << this->id << "/connect received a " << method << " message ";
	Address peerAddress = networkMessage.SenderAddress();
	std::string peerId = json::parse(DataParser::FetchContent(networkMessage.Body()))["node_id"];
	peers[peerId] = peerAddress;
	return {{"node_id", this->id}};
}