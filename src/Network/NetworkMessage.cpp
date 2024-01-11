//
// Created by lukasz on 15.12.23.
//

#include <Network/NetworkMessage.hpp>

namespace Network {
	NetworkMessage::NetworkMessage(uint32_t id, MessageType type, Address senderAddress, Address receiverAddress,
	                               std::string body) : m_id(id), m_messageType(type),
	                                                   m_senderAddress(senderAddress),
	                                                   m_receiverAddress(receiverAddress),
	                                                   m_body(std::move(body)) {
	}

	NetworkMessage::NetworkMessage(uint32_t id, Address senderAddress, Address receiverAddress, std::string body)
			: m_id(id), m_senderAddress(senderAddress), m_receiverAddress(receiverAddress),
			  m_body(std::move(body)) {
		m_messageType = MessageType::Request;
	}

	uint32_t NetworkMessage::Id() {
		return this->m_id;
	}

	std::string NetworkMessage::Body() {
		return this->m_body;
	}

	json NetworkMessage::Json() {
		return json::parse(this->m_body);
	}


	MessageType NetworkMessage::Type() {
		return this->m_messageType;
	}

	Address NetworkMessage::SenderAddress() {
		return this->m_senderAddress;
	}

	Address NetworkMessage::ReceiverAddress() {
		return this->m_receiverAddress;
	}
}