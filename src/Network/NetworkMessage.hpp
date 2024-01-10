//
// Created by lukasz on 03.12.23.
//

#include <string>
#include <utility>
#include <random>
#include <Address.hpp>
#include "../../external/nlohmann/json.hpp"

using json = nlohmann::json;

#ifndef BLOCKCHAIN_NETWORKMESSAGE_H
#define BLOCKCHAIN_NETWORKMESSAGE_H

namespace Network {
	enum class MessageType : uint8_t {
		Broadcast,
		Request,
		Response,
		Ping,
	};


	class NetworkMessage {
	protected:
		uint32_t m_id = 0;
		Address m_senderAddress = Address("0", "0");
		Address m_receiverAddress = Address("0", "0");
		MessageType m_messageType = MessageType::Ping;
		std::string m_body = " ";

	public:
		NetworkMessage() = default;

		NetworkMessage(uint32_t id, MessageType type, Address senderAddress, Address receiverAddress,
		               std::string message);

		NetworkMessage(uint32_t id, Address senderAddress, Address receiverAddress, std::string message);

		uint32_t Id();

		std::string Body();

		MessageType Type();

		Address SenderAddress();

		Address ReceiverAddress();

		json Json();
	};
}


#endif //BLOCKCHAIN_NETWORKMESSAGE_H
