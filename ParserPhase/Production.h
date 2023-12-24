//
// Created by deffo on 24/12/23.
//

#ifndef COMPILER_PRODUCTION_H
#define COMPILER_PRODUCTION_H


#include "Common.h"
#include "Symbol.h"

class Production {
public:
    NonTerminal* lhs;
    std::vector<Symbol*> rhs;
    Production(NonTerminal* l, std::vector<Symbol*> r): lhs(l), rhs(r) {};
};

#endif //COMPILER_PRODUCTION_H
