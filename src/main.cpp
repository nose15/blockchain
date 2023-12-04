//
// Created by lukol on 26.11.2023.
//
#include "./Network.cpp"
#include "./NetworkClient.cpp"
#include "./Node.cpp"
#include "./BlockchainClient.cpp"
#include "./Transaction.cpp"


int main()
{
    Network network;
    Node node1("1", &network);
    Node node2("2", &network);

    node1.ping("2");
    node1.transaction("2", 10);

    return 0;
}