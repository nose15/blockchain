//
// Created by lukasz on 15.12.23.
//

#include <iostream>

#include <DataParser/DataParser.hpp>
#include <Utils/Utils.hpp>

std::string DataParser::FetchEndpoint(const std::string & messageBody) {
	std::vector<std::string> messageElements = Utils::SplitString(messageBody, ' ', 2);
	std::string method = messageElements[0];
	std::string endpoint = messageElements[1];

	return endpoint;
}

std::string DataParser::FetchContent(const std::string & messageBody) {
	std::vector<std::string> messageElements = Utils::SplitString(messageBody, ' ', 2);
	return messageElements[2];
}

std::string DataParser::FetchMethod(const std::string & messageBody) {
	std::vector<std::string> messageElements = Utils::SplitString(messageBody, ' ', 2);
	return messageElements[0];
}
