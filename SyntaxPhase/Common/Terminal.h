//
// Created by Meniem on 24-Dec-23.
//

#ifndef COMPILER_TERMINAL_H
#define COMPILER_TERMINAL_H


#include "Symbol.h"

class Terminal : public Symbol {
public:

    explicit Terminal(const std::string &name);
};


#endif //COMPILER_TERMINAL_H
