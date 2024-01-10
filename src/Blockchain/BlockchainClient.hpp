//
// Created by lukasz on 02.12.23.
//

#include <map>
#include <string>
#include <Blockchain/Transaction.hpp>
#include <Network/NetworkClient.hpp>
#include <DataParser/DataParser.hpp>
#include <Apps/Router.hpp>
#include <Blockchain/Blockchain.hpp>

#ifndef BLOCKCHAIN_BLOCKCHAINCLIENT_H
#define BLOCKCHAIN_BLOCKCHAINCLIENT_H

namespace Blockchain {

	class BlockchainClient {
	private:
		std::string id;
		std::map<std::string, Address> peers;
		Network::NetworkClient * networkClient;
		Router::Router router;

		json DiscoveryEndpoint(Network::NetworkMessage & networkMessage);

		json ConnectEndpoint(Network::NetworkMessage & networkMessage);

	public:
		BlockchainClient(Network::NetworkClient *);

		void DiscoverPeers(const std::vector<Address> & initialPeers);

		void MakeTransaction(std::string & receiverId, uint32_t amount);

		Network::NetworkMessage MessageHandler(Network::NetworkMessage &);
	};
}



#endif //BLOCKCHAIN_BLOCKCHAINCLIENT_H
