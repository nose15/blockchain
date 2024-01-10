//
// Created by lukol on 29.11.2023.
//

#include <Network/NetworkClient.hpp>

namespace Network {
	NetworkClient::NetworkClient(std::string nodeId, NetworkSim * network) : nodeId(std::move(nodeId)), network(network) {
		try {
			this->ipAddress = network->connect(
					[this](NetworkMessage networkMessage) { this->MessageHandler(networkMessage); });
			std::cout << "NetworkClient for " << this->nodeId << " established" << std::endl;
		} catch (std::runtime_error & error) {
			throw std::runtime_error("NetworkSim Client could not be established (" + (std::string) error.what() + ")");
		}
	}

	NetworkMessage NetworkClient::SendRequest(const Address & receiverAddress, const std::string & responsePort,
	                                          const std::string & message) {
		std::promise<NetworkMessage> pendingResponse;
		std::future<NetworkMessage> responseFuture = pendingResponse.get_future();
		uint32_t requestId = Utils::generateRandomId();

		PendingRequest pendingRequest(requestId, responseFuture, pendingResponse);
		pendingRequests.push_back(pendingRequest);

		NetworkMessage networkMessage(requestId, Request, Address(ipAddress, responsePort), receiverAddress, message);

		try {
			this->network->SendMessage(networkMessage);
			NetworkMessage response = responseFuture.get();
			return response;
		} catch (std::runtime_error & error) {
			throw std::runtime_error("Request failed (" + (std::string) error.what() + ")");
		}
	}

// TODO: Consider the right order of handling the message. What should be handled first, Endpoint or Type?
	void NetworkClient::MessageHandler(NetworkMessage & networkMessage) {
		switch (networkMessage.Type()) {
			case Response: {
				ResponseHandler(networkMessage);
				break;
			}
			case Request: {
				try {
					network->SendMessage(RequestHandler(networkMessage));
				} catch (std::runtime_error & error) {
					throw std::runtime_error("Could not send message - " + (std::string) error.what());
				}
				break;
			}
			case Broadcast: {
				std::cout << this->nodeId << " received a broadcasted message" << std::endl;
				break;
			}
			default: {
				break;
			}
		}
	}

	NetworkMessage && NetworkClient::RequestHandler(NetworkMessage & networkMessage) {
		if (networkMessage.Type() != Request) {
			throw std::runtime_error("Invalid message type - should be \"Request\"");
		}

		std::string port = networkMessage.SenderAddress().port;

		try {
			std::function<NetworkMessage(NetworkMessage &)> portHandler = portHandlers[port];
			return std::move(portHandler(networkMessage));
		} catch (const std::bad_function_call & e) {
			return NetworkMessage(networkMessage.Id(), Response,
			                      Address(this->ipAddress, networkMessage.ReceiverAddress().port),
			                      networkMessage.SenderAddress(), "404");
		}
	}


	void NetworkClient::ResponseHandler(NetworkMessage & networkMessage) {
		if (networkMessage.Type() != Response) {
			throw std::runtime_error("Invalid message type - should be \"Response\"");
		}

		for (auto pendingRequest: this->pendingRequests) {
			if (pendingRequest.GetId() == networkMessage.Id()) {
				pendingRequest.Resolve(networkMessage);
				return;
			}
		}

		throw std::runtime_error("Received response but there was no request");
	}

	void
	NetworkClient::AddPortHandler(const std::string & port,
	                              const std::function<NetworkMessage(NetworkMessage &)> & handler) {
		auto iter = portHandlers.find(port);
		if (iter != portHandlers.end()) throw std::runtime_error("This port is already occupied");

		std::pair<std::string, std::function<NetworkMessage(NetworkMessage &)>> handlerPair(port, handler);

		portHandlers.insert(handlerPair);
	}

	void NetworkClient::BroadcastMessage(const std::string & message) {
		//TODO: Add NetworkMessageFactory
		uint32_t id = Utils::generateRandomId();
		NetworkMessage networkMessage(id, Broadcast, Address(ipAddress, "0"), Address("0", "0"), message);
		network->SendMessage(networkMessage);
	}

	void NetworkClient::disconnect() {
		this->network->disconnect(this->ipAddress);
		this->network = nullptr;
	} // TODO: Connect method, so the client can be reused


	const std::string & NetworkClient::getIp() { return this->ipAddress; }


}
