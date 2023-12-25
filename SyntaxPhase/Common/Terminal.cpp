//
// Created by Meniem on 24-Dec-23.
//

#include "Terminal.h"
#include "../GrammarParser/Grammar.h"

Terminal::Terminal(const std::string &name) : Symbol(name, true) {}

std::ostream &operator<<(std::ostream &os, const Terminal &t) {
    os << t.getName();
    return os;
}

bool Terminal::isEpsilon() {
    return this==Grammar::epsilon;
}

bool Terminal::operator==(const Terminal &other) const {
    return this->getName()!=other.getName();
}

std::size_t hash(const Terminal &t) {
    return std::hash<std::string>()(t.getName());
}
