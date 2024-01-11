//
// Created by lukasz on 02.12.23.
//

#include <map>
#include <string>
#include <Blockchain/Transaction.hpp>
#include <Network/Network.hpp>
#include <DataParser/DataParser.hpp>
#include <Apps/Router.hpp>

#ifndef BLOCKCHAIN_BLOCKCHAINCLIENT_H
#define BLOCKCHAIN_BLOCKCHAINCLIENT_H

namespace Blockchain {

	class BlockchainClient {
	private:
		uint8_t id;
		std::map<uint8_t, Address> peers;
		std::shared_ptr<Network::NetworkClient> networkClient;
		Router::Router router;

		json DiscoveryEndpoint(Network::NetworkMessage & networkMessage);

		json ConnectEndpoint(Network::NetworkMessage & networkMessage);

	public:
		BlockchainClient(std::shared_ptr<Network::NetworkClient> networkClient);

		void DiscoverPeers(const std::vector<Address> & initialPeers);

		void MakeTransaction(uint8_t receiverId, uint32_t amount);

		Network::NetworkMessage MessageHandler(Network::NetworkMessage &);
	};
}



#endif //BLOCKCHAIN_BLOCKCHAINCLIENT_H
