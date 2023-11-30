//
// Created by Meniem on 29-Nov-23.
//

#include "RulesConverter.h"

int RulesConverter::linesCounter;

RulesConverter::RulesConverter(std::string filePath) : filePath(std::move(filePath)) {}

const std::vector<RegularExpression> &RulesConverter::getRegularExpressions() const {
    return regularExpressions;
}

int RulesConverter::parseFile() {
    std::ifstream file(filePath);
    if (!file.is_open()){
        std::cerr << "Unable to open file" << "\n";
        return -1;
    }
    std::string line;
    while(getline(file, line)){
        linesCounter++;
        trimBlanksFromEnds(line);
        int type = checkType(line);
        switch (type){
            case KEYWORDS:
                keywordsHandler(line);
                break;
            case PUNCTUATION:
                punctuationHandler(line);
                break;
            case REGULAR_DEFINITION: {
                int statusCode = regularDefinitionHandler(line);
                if (statusCode == -1){
                    std::cerr << linesCounter << ": '-' range keyword is not used properly." << "\n";
                    return -1;
                }

                break;
            }
            case REGULAR_EXPRESSION: {
                int statusCode = regularExpressionHandler(line);
                if (statusCode == -1){
                    std::cerr << linesCounter << ": '-' range keyword is not used properly." << "\n";
                    return -1;
                }
                break;
            }
            default:
                return -1;
        }

    }

    file.close();

    // Convert all keywords to regular expressions with the highest priority
    for (const std::string& keyword: allKeywords){
        RegularExpression regularExpression(keyword, keyword, 0);
        regularExpressions.push_back(regularExpression);
    }

    // Convert all punctuation symbols to regular expressions with the second-highest priority
    for (const std::string& punctuation: allPunctuation){
        RegularExpression regularExpression(punctuation, punctuation, 1);
        regularExpressions.push_back(regularExpression);
    }

    // Sort Regular Expressions by priority
    std::sort(regularExpressions.begin(), regularExpressions.end(),
              [](const RegularExpression &a, const RegularExpression &b) {
                  return a.getPriority() < b.getPriority();
              });

    return 0;
}

bool RulesConverter::isRegularDefinition(std::string str) {
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

bool RulesConverter::isRegularExpression(std::string str) {
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

int RulesConverter::checkType(std::string str) {
    if (str.front() == '{' && str.back() == '}')
        return KEYWORDS;
    if (str.front() == '[' && str.back() == ']')
        return PUNCTUATION;
    if (isRegularDefinition(str))
        return REGULAR_DEFINITION;
    if (isRegularExpression(str))
        return REGULAR_EXPRESSION;

    std::cerr << linesCounter << ": Unidentified Line" << "\n";
    return -1;
}

void RulesConverter::keywordsHandler(std::string str) {
    removeFirstAndLastChars(str);
    trimBlanksFromEnds(str);
    removeConsecutiveSpaces(str);
    std::vector<std::string> keywords = split(str, ' ');
    for (const std::string& keyword: keywords)
        allKeywords.push_back(keyword);
}

void RulesConverter::punctuationHandler(std::string str) {
    removeFirstAndLastChars(str);
    trimBlanksFromEnds(str);
    removeConsecutiveSpaces(str);
    std::vector<std::string> punctuations = split(str, ' ');
    for (const std::string& punctuation: punctuations)
        allPunctuation.push_back(punctuation);
}

int RulesConverter::regularDefinitionHandler(std::string str) {
    removeConsecutiveSpaces(str);
    std::pair<std::string, std::string> splitString = splitIntoTwo(str, '=');
    trimBlanksFromEnds(splitString.first);
    trimBlanksFromEnds(splitString.second);
    RegularDefinition regularDefinition(splitString.first, splitString.second);
    int statusCode = regularDefinition.standardizeRegex(regularDefinitions);
    if (statusCode == -1)
        return -1;
    regularDefinitions.push_back(regularDefinition);
    return 0;
}

int RulesConverter::regularExpressionHandler(std::string str) {
    removeConsecutiveSpaces(str);
    std::pair<std::string, std::string> splitString = splitIntoTwo(str, ':');
    trimBlanksFromEnds(splitString.first);
    trimBlanksFromEnds(splitString.second);
    // Create Regular Expressions where it's priority starts from 2 as 0 and 1 are reserved for keywords and punctuation.
    RegularExpression regularExpression(splitString.first, splitString.second, (int) regularExpressions.size() + 2);
    int statusCode = regularExpression.standardizeRegex(regularDefinitions);
    if (statusCode == -1)
        return -1;
    regularExpressions.push_back(regularExpression);
    return 0;
}




