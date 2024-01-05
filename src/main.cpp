//
// Created by lukol on 26.11.2023.
//
#include "Network/Network.h"
#include "Network/NetworkClient.h"
#include "Node/Node.h"

// TODO: Separate public from private headers so all the components can be more independent
// TODO: Request class that inherits from the NetworkMessage
// TODO: Learn and implement: error handling and tests
// TODO: Logging system, so it doesn't throw everything to the terminal window
// TODO: Network message builder
// TODO: Learn and implement: move enums out of the header files

// TODO: App framework and separation from the network

int main()
{
    Network network;

    // create initial peers
    // create peers and connect them to the initial peers

    std::vector<Node> initialNodes;

    for (int i = 0; i < 5; i++)
    {
        initialNodes.emplace_back(std::to_string(i), &network);
    }

    for (int i = 5; i < 50; i++)
    {
        Node node(std::to_string(i), &network);
        Address address(initialNodes[i % 5].networkClient->getIp(), "8000");
        std::vector<Address> addresses = {address};
        node.blockchainClient->DiscoverPeers(addresses);
    }

    std::cout << std::endl;
    for (Node node : initialNodes){
        std::cout << "Node " << node.getId() << ": ";
        Utils::PrintMap(node.blockchainClient->peers);
        std::cout << std::endl;
    }



    return 0;
}