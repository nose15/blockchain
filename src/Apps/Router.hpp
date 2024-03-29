//
// Created by lukasz on 17.12.23.
//

#include <map>
#include <string>
#include <utility>
#include <Network/NetworkMessage.hpp>
#include <DataParser/DataParser.hpp>

#ifndef BLOCKCHAIN_ROUTER_H
#define BLOCKCHAIN_ROUTER_H

namespace Router {
	class Router;
}

class Router::Router {
protected:
	std::map<std::string, std::function<json(Network::NetworkMessage &)>> m_endpoints;
public:
	Router();

	Router(std::map<std::string, std::function<json(Network::NetworkMessage &)>> endpoints);

	void AddEndpoint(std::string path, std::function<json(Network::NetworkMessage &)> handler);

	std::function<json(Network::NetworkMessage &)> & Dispatch(const std::string & endpoint);
};


#endif //BLOCKCHAIN_ROUTER_H
