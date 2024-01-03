//
// Created by lukasz on 17.12.23.
//

#include <utility>

#include "Router.h"

Router::Router() = default;

Router::Router(std::map<std::string, std::function<json(NetworkMessage &)>> endpoints)
    : m_endpoints(std::move(endpoints)) {}

std::function<json(NetworkMessage &)> &Router::Dispatch(const std::string& endpoint) {
    return this->m_endpoints.at(endpoint);
}

void Router::AddEndpoint(std::string path, std::function<json(NetworkMessage &)> handler) {
    m_endpoints.insert(std::pair<std::string, std::function<json(NetworkMessage &)>>(path, handler));
}
