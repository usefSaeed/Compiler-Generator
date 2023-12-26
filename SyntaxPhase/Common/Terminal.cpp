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
