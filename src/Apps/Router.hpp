//
// Created by lukasz on 17.12.23.
//

#include <map>
#include <string>
#include <utility>
#include <Network/NetworkMessage.hpp>
#include <DataParser/DataParser.hpp>
#include <Apps/Router.hpp>

#ifndef BLOCKCHAIN_ROUTER_H
#define BLOCKCHAIN_ROUTER_H


class Router {
private:
	std::map<std::string, std::function<json(NetworkMessage &)>> m_endpoints;
public:
	Router();

	Router(std::map<std::string, std::function<json(NetworkMessage &)>> endpoints);

	void AddEndpoint(std::string path, std::function<json(NetworkMessage &)> handler);

	std::function<json(NetworkMessage &)> & Dispatch(const std::string & endpoint);
};


#endif //BLOCKCHAIN_ROUTER_H
