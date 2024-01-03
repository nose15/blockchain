//
// Created by lukol on 26.11.2023.
//
#include "Network/Network.h"
#include "Network/NetworkClient.h"
#include "Node/Node.h"

// TODO: Separate public from private headers so all the components can be more independent
// TODO: Router for applications
// TODO: Message parser
// TODO: Request class that inherits from the NetworkMessage
// TODO: Learn and implement: error handling and tests
// TODO: Logging system, so it doesn't throw everything to the terminal window
// TODO: Network message builder
// TODO: Learn and implement: move enums out of the header files

// TODO: App framework and separation from the network

int main()
{
    Network network;
    Address address1("1", "8000");
    Address address2("2", "8000");
    Address address3("3", "8000");

    std::vector<Address> addresses1 = {address2, address3};
    std::vector<Address> addresses2 = {address1, address3};
    std::vector<Address> addresses3 = {address1, address2};

    Node node1("1", &network);
    Node node2("2", &network);
    Node node3("3", &network);

    node1.BlockchainTest(addresses1);
    node2.BlockchainTest(addresses2);
    node3.BlockchainTest(addresses3);

    return 0;
}