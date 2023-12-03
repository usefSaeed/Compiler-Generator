//
// Created by Meniem on 24-Nov-23.
//

#include "Util.h"
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
    size_t start = 0, end;

    if (str.empty())
        return tokens;

    if (str.find(delimiter, start) == std::string::npos)
        return {str};

    while ((end = str.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

void trimBlanksFromEnds(std::string& str){
    const std::string& blanks = " \t\n\r";
    str.erase(str.find_last_not_of(blanks)+1);
    str.erase(0, str.find_first_not_of(blanks));
}

void removeConsecutiveSpaces(std::string& str) {
    std::string result;
    bool seenSpace = false;

    for (char ch : str) {
        if (std::isspace(ch)) {
            if (!seenSpace) {
                result += ' ';
                seenSpace = true;
            }
        } else {
            result += ch;
            seenSpace = false;
        }
    }
    str = result;
}

void removeSpaces(std::string& str) {
    std::string result;
    for (char ch : str) {
        if (ch != ' ') {
            result += ch;
        }
    }
    str = result;
}

void removeFirstAndLastChars(std::string& str){
    if (str.size()>2) {
        str.erase(0, 1);
        str.erase(str.length()-1);
    }
}

std::string joinStrings(const std::vector<std::string>& strings, char separator) {
    std::ostringstream oss;
    if (!strings.empty()) {
        oss << strings.front();
        for (auto it = std::next(strings.begin()); it != strings.end(); ++it) {
            oss << separator << *it;
        }
    }
    return oss.str();
}

std::pair<std::string, std::string> splitIntoTwo(const std::string& str, char delimiter){
    size_t pos = str.find(delimiter);
    if (pos != std::string::npos){
        std::string before = str.substr(0, pos);
        std::string after = str.substr(pos + 1);
        return make_pair(before, after);
    }
    return make_pair(str, std::string {});
}
std::string replaceAll(std::string& str, const std::string& target, const std::string& replacer) {
    std::size_t found = str.find(target);
    while (found != std::string::npos) {
        str.replace(found, 2, replacer);
        found = str.find(target, found + 1);
    }
    return str;
}

