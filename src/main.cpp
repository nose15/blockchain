//
// Created by lukol on 26.11.2023.
//
#include "./Network.cpp"
#include "./NetworkClient.cpp"
#include "./Node.cpp"


int main()
{
    Network network;
    Node node1("1", &network);
    Node node2("2", &network);

    node1.ping("2");

    return 0;
}