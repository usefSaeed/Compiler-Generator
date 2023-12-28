#include "ParsingTrace.h"

ParsingTrace::ParsingTrace(std::stack<Symbol*> s, std::vector<Token>& in, int l)
    :stack(s), input(in), lookahead(l) {};

void ParsingTrace::setError(std::string err) {
    this->err = err;
}

void ParsingTrace::setResult(std::string result) {
    this->result = result;
}

void printStackTrace(std::ostream &os, std::stack<Symbol*> stack, bool topFirst = false) {
    int n = stack.size();
    std::vector<Symbol*> symbols(n);

    for (int i=0; i < n; i++) {
        auto top = stack.top();
        stack.pop();
        if (topFirst) {
            symbols[i] = top;
        } else {
            symbols[n - i - 1] = top;
        }
    }

    for (int i=0; i < n; i++) {
        os << symbols[i]->getName() << " ";
    }
}

void printInputTrace(std::ostream &os, std::vector<Token> input, int l) {
    for (int i=l; i < input.size(); i++) {
        os << input[i].lexeme;
    }
}

void ParsingTrace::printStack() {
    printStackTrace(std::cout, this->stack, true);
}

std::ostream &operator<<(std::ostream &os, const ParsingTrace& trace) {
    printStackTrace(os, trace.stack);
    os << "\t\t";
    printInputTrace(os, trace.input, trace.lookahead);
    os << "\t\t";
    os << trace.err;
    os << trace.result;
    os << std::endl;
    return os;
}