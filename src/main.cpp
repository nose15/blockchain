//
// Created by lukol on 26.11.2023.
//
#include "Network/Network.cpp"
#include "Network/NetworkClient.cpp"
#include "./Node.cpp"
#include "Blockchain/BlockchainClient.cpp"
#include "Blockchain/Transaction.cpp"
#include "Network/PendingRequest.cpp"
#include "./Utils.cpp"
#include "Network/NetworkMessage.cpp"

// TODO: Router for applications
// TODO: Message parser
// TODO: RequestTest class that inherits from the NetworkMessage
// TODO: Learn and implement: error handling and tests
// TODO: Logging system, so it doesn't throw everything to the terminal window
// TODO: Network message builder
// TODO: Learn and implement: move enums out of the header files

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