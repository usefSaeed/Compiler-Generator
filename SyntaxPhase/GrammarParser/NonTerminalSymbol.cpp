//
// Created by Meniem on 19-Dec-23.
//

#include "NonTerminalSymbol.h"
#include <utility>

NonTerminalSymbol::NonTerminalSymbol(std::string name, productionsVector productions) : name(std::move(
        name)), productions(std::move(productions)) {}

const std::string &NonTerminalSymbol::getName() const {
    return name;
}


const productionsVector &NonTerminalSymbol::getProductions() const {
    return productions;
}

std::string NonTerminalSymbol::toString() const {
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

void NonTerminalSymbol::setProductions(const productionsVector &productionsVector) {
    NonTerminalSymbol::productions = productionsVector;
}


