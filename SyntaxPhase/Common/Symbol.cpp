//
// Created by Meniem on 24-Dec-23.
//

#include "Symbol.h"

#include <utility>

Symbol::Symbol(std::string name, bool terminal) : name(std::move(name)), terminal(terminal) {}

const std::string &Symbol::getName() const {
    return name;
}

bool Symbol::isTerminal() const {
    return terminal;
}
