//
// Created by lukasz on 08.12.23.
//

#ifndef BLOCKCHAIN_UTILS_H
#define BLOCKCHAIN_UTILS_H


class Utils {
public:
    static unsigned int generateRandomId();

    static std::vector<std::string> SplitString(const std::string& str, char separator);
};


#endif //BLOCKCHAIN_UTILS_H
