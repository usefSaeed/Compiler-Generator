//
// Created by deffo on 24/12/23.
//

#include "Parser.h"
#include "ParsingTrace.h"
#include "ParsingResult.h"
#include "../FirstAndFollowGenerator/FollowSetsGenerator.h"
#include "../FirstAndFollowGenerator/FirstSetsGenerator.h"

#include <iomanip>
#include <fstream>

Parser::Parser(Grammar& cfg): grammar(cfg), NTs(cfg.getStandardizedNonTerminals())
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
        index++;
        return *endToken;
    }
    return input[index++];
}

std::string productionString(Production &production, NonTerminal* nonTerminal);


ParsingResult Parser::parse(std::vector<Token> &input)
{
    if (input.empty())
        return ParsingResult();

    Symbol *startSymbol = this->startingSymbol;
    auto *rootNode = new ParsingTreeNode(startSymbol);

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
                auto err = "Error: missing '" + currentSymbol->getName() + "', inserted";
                trace.setError(err);
                traces.push_back(trace);
                continue;
            }

            traces.push_back(trace);
            lookahead = nextToken(input, lookaheadIndex);
        }
        else
        {
            auto *currentNonTerminal = dynamic_cast<NonTerminal *>(currentSymbol);

            bool entryExists = parsingTable.contains({currentNonTerminal, lookahead.terminal});
            if (!entryExists && lookahead.terminal == END) {
                auto err = "Error: missing '" + currentSymbol->getName() + "'";
                trace.setError(err);
                traces.push_back(trace);
                continue;
            }
            else if (!entryExists)
            {
                auto err = "Error: illegal {" + currentSymbol->getName() + "} - discarded " 
                            + (!lookahead.lexeme.empty() ? "'" + lookahead.lexeme + "'" : lookahead.terminal);
                trace.setError(err);
                traces.push_back(trace);

                lookahead = nextToken(input, lookaheadIndex);
                stack.push(currentNonTerminal);
                nodes.push(currentNode);
                continue;
            }

            ParsingTableEntry entry = parsingTable[{currentNonTerminal, lookahead.terminal}];
            if (entry.isSync())
            {
                auto err = "Error: expected '" + currentSymbol->getName() + "'";
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
                Symbol* symbol = (*it).get();
                stack.push(symbol);

                auto n = new ParsingTreeNode(symbol);
                currentNode->addChild(n);
                nodes.push(n);
            }
        }
    }

    auto tree = ParsingTree(rootNode);
    return ParsingResult(tree, traces);
}

std::string productionString(Production &production, NonTerminal* nonTerminal)
{
    std::stringstream ss;
    ss << nonTerminal->getName();
    ss << " -> ";
    
    bool isEpsilonProduction = production.empty();
    
    if (isEpsilonProduction) {
        ss << "\u03B5";
    } else {
        for (const auto& symbol : production)
        {
            ss << symbol->getName();
        }
    }
    return ss.str();
}


void Parser::computeNTsWithFirstSet() {
    FirstSetsGenerator firstSG(NTs);
}

void Parser::computeNTsWithFollowSet() {
    FollowSetsGenerator followSG(NTs, grammar.getStartSymbol());
}

Production Parser::getInputMatchedProduction(const std::vector<std::vector<std::shared_ptr<Symbol>>>& productions, const std::string& input){
    for (std::vector<std::shared_ptr<Symbol>> production: productions) {
        NonTerminal nonTerminal("production");
        std::vector<std::vector<std::shared_ptr<Symbol>>> pTemplate;
        pTemplate.push_back(production);
        nonTerminal.setProductions(pTemplate);
        nonTerminal.computeFirst();
        for (Terminal* element :nonTerminal.getFirstSet()->getSet()) {
            if (element->getName() == input){
                return production;
            }
        }
    }

}

void Parser::constructParseTable() {
    for (const std::shared_ptr<NonTerminal>& nonTerminal: NTs){
        std::shared_ptr<FirstSet> firstSet = nonTerminal->getFirstSet();
        std::shared_ptr<FollowSet> followSet = nonTerminal->getFollowSet();
        std::vector<std::vector<std::shared_ptr<Symbol>>> productions = nonTerminal->getProductions();
        for (Terminal* first: firstSet->getSet()){
           if (!first->isEpsilon()){
               parsingTable[std::pair(nonTerminal.get(),first->getName())] = ParsingTableEntry(getInputMatchedProduction(productions, first->getName()));
           }
        }

        for (Terminal* follow: followSet->getSet()){
            if (!parsingTable.contains({nonTerminal.get(), follow->getName()})){
                if (firstSet->hasNoEpsilon()) {
                    parsingTable[std::pair(nonTerminal.get(),follow->getName())] = ParsingTableEntry("sync");
                } else {
                    parsingTable[std::pair(nonTerminal.get(),follow->getName())] = ParsingTableEntry("epsilon");
                }
            }
        }
    }
}

void Parser::printParsingTable() {
    const int columnWidth = 25;
    std::cout << std::endl;
    std::cout << std::setw( 2 * columnWidth - 15) << "Parsing Table" << std::endl;
    std::cout << std::left << std::setw(columnWidth) << "NonTerminal"
              << std::setw(columnWidth) << "Terminal"
              << "Entry" << std::endl;

    for (const auto& entry : parsingTable) {
        auto key = entry.first;
        auto value = entry.second;

        if (key.first && !key.second.empty()) {
            std::cout << std::left << std::setw(columnWidth) << key.first->getName() /* NonTerminal */
                      << std::setw(columnWidth) << key.second /* Terminal */
                      << (value.isEpsilon() ? "epsilon" : (value.isSync() ? "sync" : "production")) /* Entry */
                      << std::endl;
        } else {
            std::cerr << "Error: Invalid key in parsingTable." << std::endl;
        }
    }
}


void Parser::writeParsingTableToCSV() {
    std::string filename = "./parsingTable.csv";
    std::ofstream csvFile(filename);

    if (!csvFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return;
    }

    csvFile << "NonTerminal,Terminal,Entry" << std::endl;

    for (const auto& entry : parsingTable) {
        auto key = entry.first;
        auto value = entry.second;

        if (key.first && !key.second.empty()) {
            csvFile << key.first->getName()
                    << "," << key.second
                    << "," << (value.isEpsilon() ? "epsilon" : (value.isSync() ? "sync" : "production")) /* Entry */
                    << std::endl;
        } else {
            std::cerr << "Error: Invalid key in parsingTable." << std::endl;
        }
    }

    csvFile.close();
}