//
// Created by Meniem on 29-Nov-23.
//

#include "RulesConverter.h"

RulesConverter::RulesConverter(std::string filePath) : filePath(std::move(filePath)) {}

const std::vector<RegularExpression> &RulesConverter::getRegularExpressions() const {
    return regularExpressions;
}

int RulesConverter::ParseFile() {
    std::ifstream file(filePath);
    if (!file.is_open()){
        std::cerr << "Unable to open file" << "\n";
        return -1;
    }
    std::string line;
    while(getline(file, line)){
        trimBlanksFromEnds(line);
        int type = CheckType(line);

    }

    file.close();
    return 0;
}

bool RulesConverter::IsRegularDefinition(std::string str) {
    // Finds first occurrence of '='
    size_t pos = str.find('=');

    // if '=' exists in the string
    if (pos != std::string::npos) {
        char before = str.at(pos - 1); // character before '='
        if (before != '\\')
            return true;
    }
    return false;
}

bool RulesConverter::IsRegularExpression(std::string str) {
    // Finds first occurrence of ':'
    size_t pos = str.find(':');

    // if ':' exists in the string
    if (pos != std::string::npos) {
        char before = str.at(pos - 1); // character before ':'
        if (before != '\\')
            return true;
    }
    return false;
}

int RulesConverter::CheckType(std::string str) {
    if (str.front() == '{' && str.back() == '}')
        return KEYWORDS;
    if (str.front() == '[' && str.back() == ']')
        return PUNCTUATION;
    if (IsRegularDefinition(str))
        return REGULAR_DEFINITIONS;
    size_t pos = str.find(':');
    if (IsRegularExpression(str))
        return REGULAR_EXPRESSIONS;

    std::cerr << "Unidentified Line" << "\n";
    return -1;
}
