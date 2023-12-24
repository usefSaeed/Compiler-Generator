//
// Created by deffo on 24/12/23.
//

#include "Parser.h"


Parser::Parser(CFGrammar& cfg): grammar(cfg) {
    computeFirstSet();
    computeFollowSet();
    constructParseTable();
}

Token& nextToken(std::vector<Token>& input, int& index) {
    return input[index++];
};

ParsingTree Parser::parse(std::vector<Token>& input) {
    // TODO: protect against empty input vector
    // TODO: create syntax tree (create from left to right - leaf to root)

    int lookaheadIndex = 0;
    Token& lookahead = nextToken(input, lookaheadIndex);

    std::stack<Symbol*> stack;
    stack.push(this->grammar.startSymbol);

    while (!stack.empty()) {
        Symbol* currentSymbol = stack.top(); stack.pop();

        if (currentSymbol->isTerminal()) {
            bool match = currentSymbol->name == lookahead.terminal.name;
            if (!match) {
                // TODO: handle error
            }

            lookahead = nextToken(input, lookaheadIndex);
        } else {
            Production* production = parseTable[{currentSymbol, lookahead.terminal}];

            for (auto& symbol: production->rhs)
                stack.push(symbol);
        }
    }
}


void Parser::computeFirstSet() {}
void Parser::computeFollowSet() {}
void Parser::constructParseTable() {}