//
// Created by Meniem on 28-Nov-23.
//

#include "RegularDefinition.h"
RegularDefinition::RegularDefinition() = default;

const std::string &RegularDefinition::getName() const {
    return name;
}

const std::string &RegularDefinition::getRegex() const {
    return regex;
}

RegularDefinition::RegularDefinition(std::string name, std::string regex) : name(std::move(name)), regex(std::move(regex)) {}

void RegularDefinition::standardizeRegex() {
    removeConsecutiveSpaces(regex);
    EnumerateRanges(regex);
}

void RegularDefinition::EnumerateRanges(std::string &str) {
    std::string result;
    for(int i = 0; i < str.length(); i++){
        char c = str[i];
        if (c != '-')
            result += c;
        else {
            if (str[i-1] == '\\') //escaped reserved '-' character
                result += c;
            else {
                // Check if there is an alphanumeric before and after the '-' with spaces or not.
                if ( (isalnum(str[i-1]) || isalnum(str[i-2])) && (isalnum(str[i+1]) || isalnum(str[i+2])) ){
                    // erase the last character added to result while handling space.
                    (str[i-1] != ' ') ? result.erase(result.size() - 1) : result.erase(result.size() - 2);
                    char beginning = (str[i-1] != ' ') ? str[i-1] : str[i-2];
                    char end = (str[i+1] != ' ') ? str[i+1] : str[i+2];
                    // Add the whole range
                    result += '(';
                    result += beginning;
                    for(char ch = beginning + 1; ch <= end; ch++){
                        result += '|';
                        result += ch;
                    }
                    result += ')';
                    // Skip the character after '-' as it's already included in the range while handling space.
                    (str[i+1] != ' ') ? i++ : i+=2;
                }
            }
        }
    }
    str = result;
}

void RegularDefinition::ReplaceDefinitions(std::string &str) {
    //todo

}



