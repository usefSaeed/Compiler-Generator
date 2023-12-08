//
// Created by usef on 12/4/2023.
//

#include "SyntaxError.h"
#include <string>
#include "iostream"

SyntaxError::SyntaxError(int st, char c) {
    this->idx = st;
    this->c = c;
}

std::ostream& operator<<(std::ostream& os, const SyntaxError& se){
    os << "Syntax Error on index:" << se.idx << " --> " << se.c << "\n";
    return os;
}
