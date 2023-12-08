//
// Created by lukol on 26.11.2023.
//
#include "./Network.cpp"
#include "./NetworkClient.cpp"
#include "./Node.cpp"
#include "./BlockchainClient.cpp"
#include "./Transaction.cpp"

// TODO: Better network infrastructure. Allow network clients to send requests and receive responses instead of just
// TODO: sending messages.

// TODO: Routing system
// TODO: Message parser

// TODO: The request has to have the id so it knows which response is his

// TODO: Basically need to rebuild the whole network and then it will become easy because then its just webdev lol

int main()
{
    Network network;
    Node node1("1", &network);
    Node node2("2", &network);

    node1.ping("2");
    node1.transaction("2", 10);

    return 0;
}