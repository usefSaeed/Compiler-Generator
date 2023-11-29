//
// Created by Meniem on 24-Nov-23.
//

#ifndef COMPILER_UTIL_H
#define COMPILER_UTIL_H
#include <vector>
#include <string>

[[nodiscard]] std::vector<std::string> split(const std::string& str, char delimiter);
[[nodiscard]] std::vector<std::string> splitWithStringDelimiter(const std::string& str, const std::string& delimiter);
void trimBlanksFromEnds(std::string& str);
void removeConsecutiveSpaces(std::string& str);
void removeSpaces(std::string& str);
void removeFirstAndLastChars(std::string& str);
[[nodiscard]] std::string JoinStrings(const std::vector<std::string>& strings, char separator);
[[nodiscard]] std::pair<std::string, std::string> SplitIntoTwo(const std::string& str, char delimiter);

#endif //COMPILER_UTIL_H
