//
// Created by usef on 12/4/2023.
//

#include "SyntaxError.h"
#include <string>
#include "iostream"

SyntaxError::SyntaxError(int st) {
    this->idx = st;
}

std::ostream& operator<<(std::ostream& os, const SyntaxError& se){
    os << "Syntax Error on index:" << se.idx << "\n";
    return os;
}
