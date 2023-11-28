//
// Created by Meniem on 24-Nov-23.
//

#ifndef COMPILER_UTIL_H
#define COMPILER_UTIL_H
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& str, char delimiter);
std::vector<std::string> splitWithStringDelimiter(const std::string& str, const std::string& delimiter);
void trimBlanksFromEnds(std::string& str);
void removeConsecutiveSpaces(std::string& str);

#endif //COMPILER_UTIL_H
