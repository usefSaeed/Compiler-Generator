//
// Created by usef on 12/6/2023.
//

#include "LATrace.h"
#include "ostream"

LATrace::LATrace(char inputChar, std::string tokenName, bool isEndOfToken) : tokenName(std::move(tokenName)){
    this->inputChar = inputChar;
    this->isEndOfToken = isEndOfToken;
}

LATrace::LATrace(char inputChar) {
    this->inputChar = inputChar;
}

std::ostream &operator<<(std::ostream &os, const LATrace &lat) {
    if (lat.isEndOfToken)
        os << "______________________\n";
    os << lat.inputChar << " --> ";
    if (!lat.tokenName.empty())
        os << lat.tokenName;
    if (lat.isEndOfToken)
        os << "#SKIP#";
    os << "\n";
    return os;
}