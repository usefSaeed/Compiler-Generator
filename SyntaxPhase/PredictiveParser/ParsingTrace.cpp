#include "ParsingTrace.h"

ParsingTrace::ParsingTrace(std::stack<Symbol*> s, std::vector<Token>& in, int l)
    :stack(s), input(in), lookahead(l) {};

void ParsingTrace::setError(std::string err) {
    this->err = err;
}

void ParsingTrace::setResult(std::string result) {
    this->result = result;
}

std::string ParsingTrace::stackString(bool topFirst) {
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
        if (topFirst) {
            stack.push(symbols[i]);
        } else {
            stack.push(symbols[n-i-1]);
        }
    }
    
    std::stringstream ss;
    for (int i=0; i < n; i++) {
        ss << symbols[i]->getName() << " ";
    }
    return ss.str();
}

std::string ParsingTrace::inputString() {
    std::stringstream ss;
    for (int i=lookahead; i < input.size(); i++) {
        ss << input[i].lexeme << " ";
    }
    return ss.str();
}

std::string ParsingTrace::extrasString() {
    std::stringstream ss;
    ss << "\033[31m"; // change color to red
    ss << err;
    ss << "\033[0m"; // reset color
    ss << result;
    return ss.str();
}
