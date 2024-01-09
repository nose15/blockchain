//
// Created by lukasz on 17.12.23.
//

#include <Apps/Router.hpp>

Router::Router() = default;

Router::Router(std::map<std::string, std::function<json(NetworkMessage &)>> endpoints)
		: m_endpoints(std::move(endpoints)) {}

std::function<json(NetworkMessage &)> & Router::Dispatch(const std::string & messageBody) {
	std::string endpoint = DataParser::FetchEndpoint(messageBody);
	return this->m_endpoints.at(endpoint);
}

void Router::AddEndpoint(std::string path, std::function<json(NetworkMessage &)> handler) {
	m_endpoints.insert(std::pair<std::string, std::function<json(NetworkMessage &)>>(path, handler));
}


