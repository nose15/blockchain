//
// Created by lukol on 26.11.2023.
//
#include "./Network.cpp"
#include "./NetworkClient.cpp"
#include "./Node.cpp"
#include "./BlockchainClient.cpp"
#include "./Transaction.cpp"
#include "./PendingRequest.cpp"
#include "./Utils.cpp"
#include "./NetworkMessage.cpp"

// TODO: Router for applications
// TODO: Message parser

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