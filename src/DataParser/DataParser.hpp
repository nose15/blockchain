//
// Created by lukasz on 15.12.23.
//

#include <map>
#include <string>
#include <Utils/Utils.hpp>

#ifndef BLOCKCHAIN_DATAPARSER_H
#define BLOCKCHAIN_DATAPARSER_H


namespace DataParser {
	std::string FetchEndpoint(const std::string & messageBody);

	std::string FetchContent(const std::string & messageBody);

	std::string FetchMethod(const std::string & messageBody);
};


#endif //BLOCKCHAIN_DATAPARSER_H
