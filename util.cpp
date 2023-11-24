//
// Created by Meniem on 24-Nov-23.
//

#include "util.h"
#include <sstream>

std::vector<std::string> split(const std::string& str, char delimiter){
    std::vector<std::string> words;
    std::string word;
    std::stringstream stringStream(str);
    while (std::getline(stringStream, word, delimiter))
        words.push_back(word);
    return words;
}

std::vector<std::string> splitWithStringDelimiter(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;

    while ((end = str.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
    }

    // Push the last token
    tokens.push_back(str.substr(start));

    return tokens;
}