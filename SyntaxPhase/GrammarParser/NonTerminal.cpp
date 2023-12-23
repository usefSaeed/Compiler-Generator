//
// Created by Meniem on 19-Dec-23.
//

#include "NonTerminal.h"
#include <utility>

NonTerminal::NonTerminal(std::string name, productionsVector productions) : name(std::move(
        name)), productions(std::move(productions)) {}

const std::string &NonTerminal::getName() const {
    return name;
}


const productionsVector &NonTerminal::getProductions() const {
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

void NonTerminal::setProductions(const productionsVector &productionsVector) {
    NonTerminal::productions = productionsVector;
}


