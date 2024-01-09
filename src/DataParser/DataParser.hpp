//
// Created by lukasz on 15.12.23.
//

#include <map>
#include <string>
#include <Utils/Utils.hpp>

#ifndef BLOCKCHAIN_DATAPARSER_H
#define BLOCKCHAIN_DATAPARSER_H


namespace DataParser {
	inline std::string FetchEndpoint(const std::string & messageBody);

	inline std::string FetchContent(const std::string & messageBody);

	inline std::string FetchMethod(const std::string & messageBody);
};


#endif //BLOCKCHAIN_DATAPARSER_H
