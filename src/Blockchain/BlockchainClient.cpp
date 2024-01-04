//
// Created by lukasz on 02.12.23.
//

#include "BlockchainClient.h"
#include "../DataParser/DataParser.h"

BlockchainClient::BlockchainClient(NetworkClient * networkClient) : networkClient(networkClient)
{
    this->id = networkClient->getIp();
    // TODO: More sophisticated id generation
    // TODO: Improve ports flexibility (allow for the ports to be assigned automatically)

    router.AddEndpoint("/discovery", [this](NetworkMessage &networkMessage) -> json { return this->DiscoveryEndpoint(networkMessage); });
    networkClient->AddPortHandler("8000", [this](NetworkMessage &networkMessage) -> NetworkMessage {
        return this->MessageHandler(networkMessage);
    });
    std::cout << "Blockchain client established" << std::endl;
}

void BlockchainClient::MakeTransaction(std::string &receiverId, int amount)
{
    Transaction transaction(this->id, receiverId, amount);
    //TODO: Mechanism that sends the BlockchainTransactionTest to all connected peers
}

NetworkMessage BlockchainClient::MessageHandler(NetworkMessage & networkMessage)
{
    // TODO: Router for endpoints
    std::function<json(NetworkMessage&)> endpointHandler = router.Dispatch(networkMessage.Body());
    json responseBody = endpointHandler(networkMessage);
    NetworkMessage responseMessage(networkMessage.Id(), Response, networkMessage.ReceiverAddress(), networkMessage.SenderAddress(), responseBody.dump());
    return responseMessage;
}

void BlockchainClient::DiscoverPeers(const std::vector<Address>& initialPeers) {
    for (const Address &peerAddress: initialPeers) {
        networkClient->SendRequest(peerAddress, "8000", R"(GET /discovery {"message": "discovery"})");
        // TODO: Figure out a way to multiple threads working on different peer chains
    }
}

void BlockchainClient::ConnectPeer(const Address & address)
{
    json jsonMessage = {{"node_id", this->id}, {"message", "discovery"}};
    std::string jsonLiteral = jsonMessage.dump();
    NetworkMessage response = networkClient->SendRequest(address, "8000", jsonLiteral);
    std::cout << response.Body() << std::endl;
    json responseJson = response.Json();

    std::string newPeerId = responseJson["node_id"];
    std::cout << this->networkClient->getIp() << " " << newPeerId << std::endl;

//    peers.insert(std::pair<std::string, Address>(newPeerId, address));
//    json peerAddressJson = responseJson["peer"];
//    Address peerAddress = Address(peerAddressJson["ip"], peerAddressJson["port"]);
//
//    if (this->peers.size() < 2) {
//        this->ConnectPeer(peerAddress);
//    }
}

// Temporarily they are here but will migrate them into a separate app framework
json BlockchainClient::DiscoveryEndpoint(NetworkMessage& networkMessage) {
    std::string method = DataParser::FetchMethod(networkMessage.Body());
    std::cout << "Blockchain Client nr." << this->id << "/discovery received a " << method << " message " << std::endl;
    std::string contentStr = DataParser::FetchContent(networkMessage.Body());
    json content = json::parse(contentStr);
    json responseMessage;

    if (content["message"] == "discovery") {
        responseMessage["node_id"] = this->id;
    }

    return responseMessage;
}
