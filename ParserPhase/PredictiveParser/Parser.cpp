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

ParsingTree Parser::parse(std::vector<Token>& input) {
    if (input.size() == 0) 
        return ParsingTree();
    
    Symbol* startSymbol = grammar.getStartSymbol();
    ParsingTreeNode* rootNode = new ParsingTreeNode(startSymbol);
    
    if (startSymbol->isTerminal()) 
        throw std::invalid_argument("startSymbol cannot be a terminal");
    
    int lookaheadIndex = 0;
    Token& lookahead = nextToken(input, lookaheadIndex);

    std::stack<Symbol*> stack;
    std::stack<ParsingTreeNode*> nodes;
    stack.push(startSymbol);
    nodes.push(rootNode);
    
    while (!stack.empty()) {
        Symbol* currentSymbol = stack.top(); stack.pop();
        ParsingTreeNode* currentNode = nodes.top(); nodes.pop();

        if (currentSymbol->isTerminal()) {
            bool match = currentSymbol->getName() == lookahead.terminal;
            if (!match) {
                // TODO: handle error
            }

            lookahead = nextToken(input, lookaheadIndex);
        } else {
            NonTerminal* current = dynamic_cast<NonTerminal*>(currentSymbol);
            ParsingTableEntry entry = parsingTable[{current, lookahead.terminal}];

            for (auto& production: entry.getProductions()) {
                for (auto& symbol: production) {
                    stack.push(symbol);
                    
                    ParsingTreeNode* n = new ParsingTreeNode(symbol);
                    currentNode->addChild(n);
                    nodes.push(n);
                }
            }
        }
    }
    
    return ParsingTree(rootNode);
}

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

