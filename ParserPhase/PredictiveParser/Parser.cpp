//
// Created by deffo on 24/12/23.
//

#include "Parser.h"
#include "ParsingTrace.h"
#include "ParsingResult.h"
#include "../FirstAndFollowGenerator/FollowSetsGenerator.h"
#include "../FirstAndFollowGenerator/FirstSetsGenerator.h"

Parser::Parser(Grammar &cfg) : grammar(cfg), NTs(cfg.getStandardizedNonTerminals())
{
    computeNTsWithFirstSet();
    computeNTsWithFollowSet();
    constructParseTable();
    startingSymbol = cfg.getStartSymbol();
}

Parser::Parser(Symbol *symbol, std::unordered_map<std::pair<NonTerminal *, std::string>, ParsingTableEntry, PairHash, PairEqual> &pt)
    : parsingTable(pt), startingSymbol(symbol) {}

Token &nextToken(std::vector<Token> &input, int &index)
{
    if (index >= input.size()) {
        auto endToken = new Token("$","");
        return *endToken;
    }
    return input[index++];
}

std::string productionString(Production &production, NonTerminal* nonTerminal);

// TODO: handle case $S | $ | S => eps
ParsingResult Parser::parse(std::vector<Token> &input)
{
    if (input.size() == 0)
        return ParsingResult();

    Symbol *startSymbol = this->startingSymbol;
    ParsingTreeNode *rootNode = new ParsingTreeNode(startSymbol);

    if (startSymbol->isTerminal())
        throw std::invalid_argument("startSymbol cannot be a terminal");

    int lookaheadIndex = 0;
    Token &lookahead = nextToken(input, lookaheadIndex);

    std::stack<Symbol *> stack;
    std::stack<ParsingTreeNode *> nodes;
    std::vector<ParsingTrace> traces;
    stack.push(startSymbol);
    nodes.push(rootNode);

    while (!stack.empty())
    {
        auto trace = ParsingTrace(stack, input, lookaheadIndex - 1);
        
        Symbol *currentSymbol = stack.top();
        stack.pop();
        ParsingTreeNode *currentNode = nodes.top();
        nodes.pop();

        if (currentSymbol->isTerminal())
        {
            bool match = currentSymbol->getName() == lookahead.terminal;
            if (!match)
            {
                auto err = "Error: missing " + currentSymbol->getName() + ", inserted";
                trace.setError(err);
                traces.push_back(trace);
                continue;
            }

            traces.push_back(trace);
            lookahead = nextToken(input, lookaheadIndex);
        }
        else
        {
            NonTerminal *currentNonTerminal = dynamic_cast<NonTerminal *>(currentSymbol);

            bool entryExists = parsingTable.contains({currentNonTerminal, lookahead.terminal});
            if (!entryExists)
            {
                auto err = "Error: (illegal " + currentSymbol->getName() + ") - discarded " + lookahead.lexeme;
                trace.setError(err);
                traces.push_back(trace);

                lookahead = nextToken(input, lookaheadIndex);
                stack.push(currentNonTerminal);
                continue;
            }

            ParsingTableEntry entry = parsingTable[{currentNonTerminal, lookahead.terminal}];
            if (entry.isSync())
            {
                auto err = "Error: expected " + currentSymbol->getName();
                trace.setError(err);
                traces.push_back(trace);
                continue;
            }

            Production production = entry.getProduction();
            trace.setResult(productionString(production, currentNonTerminal));
            traces.push_back(trace);
            
            if (entry.isEpsilon())
                continue;
            
            for (auto it = production.rbegin(); it != production.rend(); ++it)
            {
                Symbol *symbol = *it;
                stack.push(symbol);

                ParsingTreeNode *n = new ParsingTreeNode(symbol);
                currentNode->addChild(n);
                nodes.push(n);
            }
        }
    }
    
    if (lookaheadIndex < input.size()) {
        auto trace = ParsingTrace(stack, input, lookaheadIndex);
        auto err = "Finished parsing but found unexpected tokens after " + input[lookaheadIndex-1].lexeme;
        trace.setError(err);
        traces.push_back(trace);
    }

    auto tree = ParsingTree(rootNode);
    return ParsingResult(tree, traces);
}

void Parser::computeNTsWithFirstSet()
{
    FirstSetsGenerator firstSG(NTs);
    NTs = firstSG.getNTsWithFirstSets();
}

void Parser::computeNTsWithFollowSet()
{
    FollowSetsGenerator followSG(NTs, grammar.getStartSymbol());
    NTs = followSG.getNTsWithFollowSets();
}

void Parser::constructParseTable()
{
    // for (NonTerminal* nonTerminal: NTs){
    //     std::shared_ptr<FirstSet> firstSet = nonTerminal->getFirstSet();
    //     std::shared_ptr<FollowSet> followSet = nonTerminal->getFollowSet();

    //     for (Terminal* first: firstSet->getSet()){
    //        if (!first->isEpsilon()){
    //            ParsingTableEntry entry = ParsingTableEntry(nonTerminal->getProductions());
    //            parsingTable[std::pair(nonTerminal,first->getName())] = entry;
    //        }

    //     }

    //     for (Terminal* follow: followSet->getSet()){
    //         if (firstSet->hasNoEpsilon()) {
    //             parsingTable[std::pair(nonTerminal,follow->getName())] = ParsingTableEntry("sync");
    //         } else {
    //             parsingTable[std::pair(nonTerminal,follow->getName())] = ParsingTableEntry("epsilon");

    //         }
    //     }

    // }
}


std::string productionString(Production &production, NonTerminal* nonTerminal)
{
    std::stringstream ss;
    ss << nonTerminal->getName();
    ss << " -> ";
    
    bool isEpsilonProduction = production.size() == 0;
    
    if (isEpsilonProduction) {
        ss << "\u03B5";
    } else {
        for (auto symbol : production)
        {
            ss << symbol->getName();
        }
    }
    return ss.str();
}