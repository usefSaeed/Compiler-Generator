//
// Created by deffo on 24/12/23.
//

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H


#include "Common.h"
#include "Symbol.h"

class Token
{
public:
    Terminal terminal;
    std::string lexeme;
};

#endif //COMPILER_TOKEN_H
