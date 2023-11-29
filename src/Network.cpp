//
// Created by lukol on 26.11.2023.
//

#include "../include/Network.h"

Network::Network()
{
    std::cout << "Network established" << std::endl;
}

void Network::add_node(const std::string& nodeId, Node& node)
{
    std::pair<std::string, Node&> map_entry(nodeId, node);
    this->m_nodes.insert(map_entry);
    node.setNetwork(*this);
}

void Network::send(std::string senderId, std::string receiverId, std::string message)
{
    Node& receiverNode = m_nodes.find(receiverId)->second;
    receiverNode.triggerReceive(message);
}