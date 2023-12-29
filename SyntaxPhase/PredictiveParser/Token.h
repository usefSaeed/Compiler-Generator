//
// Created by deffo on 24/12/23.
//

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H


#include "Common.h"

class Token{
public:
    Token(std::string t, std::string l): terminal(t), lexeme(l) {};
    std::string terminal;
    std::string lexeme;
};

#endif //COMPILER_TOKEN_H
