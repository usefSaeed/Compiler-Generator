//
// Created by Meniem on 24-Dec-23.
//

#include "NonTerminal.h"
NonTerminal::NonTerminal(const std::string &name) : Symbol(name, false) {}

const std::vector<std::vector<Symbol>> &NonTerminal::getProductions() const {
    return productions;
}

void NonTerminal::setProductions(const std::vector<std::vector<Symbol>> &productionsVector) {
    NonTerminal::productions = productionsVector;
}
