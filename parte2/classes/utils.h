//
// Created by skidr on 26/10/2019.
//

#ifndef PARTE1_UTILS_H
#define PARTE1_UTILS_H

#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> split (string &s, string delimiter) {
    size_t pos = 0;
    std::string token;
    vector<string> result;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    result.push_back(s);
    return result;
}

#endif //PARTE1_UTILS_H
