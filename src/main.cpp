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
// TODO: Message parser - JSON like object with a possibility to serialize it into a string

int main()
{
    Network network;
    Node node1("1", &network);
    Node node2("2", &network);

    node1.Ping(Address("2", "8000"));
    node1.transaction("2", 10);

    node1.Request();

    return 0;
}