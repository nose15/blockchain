//
// Created by lukol on 26.11.2023.
//
#include <iostream>
#include <map>
#include <utility>

#include "./Network.cpp"
#include "./Node.cpp"

int main()
{
    Network network;
    Node node1("1");
    Node node2("2");

    network.add_node(node1.getId(), node1);
    network.add_node(node2.getId(), node2);

    node1.ping("2");


    return 0;
}