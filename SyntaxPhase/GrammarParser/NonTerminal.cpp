//
// Created by Meniem on 19-Dec-23.
//

#include "NonTerminal.h"
#include <utility>

NonTerminal::NonTerminal(std::string name, const std::vector<std::vector<std::string>> &productions) : name(std::move(
        name)), productions(productions) {}

const std::string &NonTerminal::getName() const {
    return name;
}


const std::vector<std::vector<std::string>> &NonTerminal::getProductions() const {
    return productions;
}

std::string NonTerminal::toString() const {
    std::string result = "Name: " + name + " Productions: ";

    for (const auto& production : productions) {
        for (const auto& symbol : production) {
            result += symbol + " ";
        }
        result.pop_back(); // Remove the extra space
        result += " | ";
    }
    result.erase(result.length()-2);

    return result;
}


