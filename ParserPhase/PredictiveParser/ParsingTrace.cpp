#include "ParsingTrace.h"

ParsingTrace::ParsingTrace(std::stack<Symbol*> s, std::vector<Token>& in, int l)
    :stack(s), input(in), lookahead(l) {};

void ParsingTrace::setError(std::string err) {
    this->err = err;
}

void ParsingTrace::setResult(std::string result) {
    this->result = result;
}

void printStackTrace(std::ostream &os, std::stack<Symbol*> stack) {
    int n = stack.size();
    std::vector<Symbol*> symbols(n);
    
    for (int i=n-1; i >= 0; i--) {
        auto top = stack.top(); stack.pop();
        symbols[i] = top;
    }
    
    for (int i=0; i < n; i++) {
        os << symbols[i]->getName();
    }

    os << "\t\t";
}

void printInputTrace(std::ostream &os, std::vector<Token> input, int l) {
    for (int i=l; i < input.size(); i++) {
        os << input[i].lexeme;
    }
    os << "\t\t";
}

std::ostream &operator<<(std::ostream &os, const ParsingTrace& trace) {
    printStackTrace(os, trace.stack);
    printInputTrace(os, trace.input, trace.lookahead);
    os << trace.err;
    os << trace.result;
    os << std::endl;
    return os;
}