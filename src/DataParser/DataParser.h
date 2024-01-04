//
// Created by lukasz on 15.12.23.
//

#include <map>
#include <string>

#ifndef BLOCKCHAIN_DATAPARSER_H
#define BLOCKCHAIN_DATAPARSER_H


class DataParser {
private:
public:
    DataParser() = delete;
    static std::string FetchEndpoint(const std::string& messageBody);
    // TODO: Method that parses maps to json
    // TODO: Method that parses JSONObject from json
    static std::string FetchContent(const std::string &messageBody);
    static std::string FetchMethod(const std::string &messageBody);
};


#endif //BLOCKCHAIN_DATAPARSER_H
