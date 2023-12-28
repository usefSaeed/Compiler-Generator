#ifndef COMPILER_PARSING_TRACE_H
#define COMPILER_PARSING_TRACE_H

#include "Common.h"
#include "Token.h"
#include "../Common/Symbol.h"

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
    void printStack();
    friend std::ostream &operator<<(std::ostream &os, const ParsingTrace &trace);
};

#endif