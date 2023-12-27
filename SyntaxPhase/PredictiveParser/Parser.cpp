//
// Created by deffo on 24/12/23.
//

#include "Parser.h"
#include "../FirstAndFollowGenerator/FollowSetsGenerator.h"
#include "../FirstAndFollowGenerator/FirstSetsGenerator.h"

Parser::Parser(Grammar& cfg): grammar(cfg), NTs(cfg.getStandardizedNonTerminals()){
    computeNTsWithFirstSet();
    computeNTsWithFollowSet();
    constructParseTable();
}

Token& nextToken(std::vector<Token>& input, int& index) {
    return input[index++];
};

//ParsingTree Parser::parse(std::vector<Token>& input) {
//    // TODO: protect against empty input vector
//    // TODO: create syntax tree (create from left to right - leaf to root)
//
//    int lookaheadIndex = 0;
//    Token& lookahead = nextToken(input, lookaheadIndex);
//
//    std::stack<Symbol*> stack;
//    stack.push(this->grammar.startSymbol);
//
//    while (!stack.empty()) {
//        Symbol* currentSymbol = stack.top(); stack.pop();
//
//        if (currentSymbol->isTerminal()) {
//            bool match = currentSymbol->name == lookahead.terminal.name;
//            if (!match) {
//                // TODO: handle error
//            }
//
//            lookahead = nextToken(input, lookaheadIndex);
//        } else {
//            Production* production = parseTable[{currentSymbol, lookahead.terminal}];
//
//            for (auto& symbol: production->rhs)
//                stack.push(symbol);
//        }
//    }
//}

void Parser::computeNTsWithFirstSet() {
    FirstSetsGenerator firstSG(NTs);
    NTs = firstSG.getNTsWithFirstSets();
}

void Parser::computeNTsWithFollowSet() {
    FollowSetsGenerator followSG(NTs, grammar.getStartSymbol());
    NTs = followSG.getNTsWithFollowSets();
}

void Parser::constructParseTable() {
    for (NonTerminal* nonTerminal: NTs){
        std::shared_ptr<FirstSet> firstSet = nonTerminal->getFirstSet();
        std::shared_ptr<FollowSet> followSet = nonTerminal->getFollowSet();

        for (Terminal* first: firstSet->getSet()){
           if (!first->isEpsilon()){
               ParsingTableEntry entry = ParsingTableEntry(nonTerminal->getProductions());
               parsingTable[std::pair(nonTerminal,first->getName())] = ParsingTableEntry(nonTerminal->getProductions());
           }

        }

        for (Terminal* follow: followSet->getSet()){
            if (firstSet->hasNoEpsilon()) {
                parsingTable[std::pair(nonTerminal,follow->getName())] = ParsingTableEntry("sync");
            } else {
                parsingTable[std::pair(nonTerminal,follow->getName())] = ParsingTableEntry("epsilon");

            }
        }

    }
}