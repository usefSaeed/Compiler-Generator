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
        switch (type){
            case KEYWORDS:
                std::cout << "Keyword" << "\n";
                KeywordsHandler(line);
                break;
            case PUNCTUATION:
                std::cout << "Punctuation" << "\n";
                PunctuationHandler(line);
                break;
            case REGULAR_DEFINITION:
                std::cout << "Regular Definition" << "\n";
                RegularDefinitionHandler(line);
                break;
            case REGULAR_EXPRESSION:
                std::cout << "Regular Expression" << "\n";
                break;
            default:
                break;
        }

    }

    file.close();

    // Accumulate all Keywords and add it to one regular expression with the highest priority
    if (!allKeywords.empty()){
        std::string regex = JoinStrings(allKeywords, '|');
        RegularExpression regularExpression("keywords", regex, 0);
        regularExpression.standardizeRegex();
        regularExpressions.push_back(regularExpression);
    }

    // Accumulate all Punctuation and add it to one regular expression with the second-highest priority
    if (!allPunctuation.empty()){
        std::string regex = JoinStrings(allPunctuation, '|');
        RegularExpression regularExpression("punctuation", regex, 1);
        regularExpression.standardizeRegex();
        regularExpressions.push_back(regularExpression);
    }

    for (const RegularExpression& regExp : regularExpressions) {
        std::cout << regExp.toString() << "\n";
    }


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
        return REGULAR_DEFINITION;
    if (IsRegularExpression(str))
        return REGULAR_EXPRESSION;

    std::cerr << "Unidentified Line" << "\n";
    return -1;
}

void RulesConverter::KeywordsHandler(std::string str) {
    removeFirstAndLastChars(str);
    trimBlanksFromEnds(str);
    removeConsecutiveSpaces(str);
    std::vector<std::string> keywords = split(str, ' ');
    for (const std::string& keyword: keywords)
        allKeywords.push_back(keyword);
}

void RulesConverter::PunctuationHandler(std::string str) {
    removeFirstAndLastChars(str);
    trimBlanksFromEnds(str);
    removeConsecutiveSpaces(str);
    std::vector<std::string> punctuations = split(str, ' ');
    for (const std::string& punctuation: punctuations)
        allPunctuation.push_back(punctuation);
}

void RulesConverter::RegularDefinitionHandler(std::string str) {
    removeSpaces(str);
    std::pair<std::string, std::string> splitString = SplitIntoTwo(str, '=');
    RegularDefinition regularDefinition(splitString.first, splitString.second);
    regularDefinition.standardizeRegex();
    regularDefinitions.push_back(regularDefinition);
}

void RulesConverter::RegularExpressionHandler(std::string str) {
    removeSpaces(str);
    std::pair<std::string, std::string> splitString = SplitIntoTwo(str, ':');
    // Create Regular Expressions where it's priority starts from 2 as 0 and 1 are reserved for keywords and punctuation.
    RegularExpression regularExpression(splitString.first, splitString.second, (int) regularExpressions.size() + 2);
    regularExpression.standardizeRegex();
    regularExpressions.push_back(regularExpression);
}
