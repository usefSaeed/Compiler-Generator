#ifndef COMPILER_PARSING_TRACE_H
#define COMPILER_PARSING_TRACE_H

#include "Common.h"
#include "Token.h"
#include "../Common/Symbol.h"

#include <sstream>

class ParsingTrace
{
private:
    std::stack<Symbol *> stack;
    std::vector<Token> input;
    int lookahead;
    std::string err;
    std::string result;

public:
    ParsingTrace(std::stack<Symbol *> stack, std::vector<Token> &input, int lookahead);
    void setError(std::string err);
    void setResult(std::string result);
    std::string stackString(bool topFirst = true);
    std::string inputString();
    std::string extrasString();
};

#endif