//
// Created by deffo on 24/12/23.
//

#include <iomanip>
#include <fstream>
#include "Parser.h"
#include "../FirstAndFollowGenerator/FollowSetsGenerator.h"
#include "../FirstAndFollowGenerator/FirstSetsGenerator.h"

Parser::Parser(Grammar& cfg): grammar(cfg), NTs(cfg.getStandardizedNonTerminals()){
    computeNTsWithFirstSet();
    std::cout << "\n\n\n";
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
    std::unordered_set<NonTerminal*> nonTerminalsSet;
    std::unordered_set<std::string> terminalsSet;

    for (const auto& entry : parsingTable) {
        nonTerminalsSet.insert(entry.first.first);
        terminalsSet.insert(entry.first.second);
    }

    // Convert sets to vectors for ordered iteration
    std::vector<NonTerminal*> nonTerminals(nonTerminalsSet.begin(), nonTerminalsSet.end());
    std::vector<std::string> terminals(terminalsSet.begin(), terminalsSet.end());
    std::sort(nonTerminals.begin(), nonTerminals.end());
    std::sort(terminals.begin(), terminals.end());

    std::ofstream csvFile(filename);

    if (!csvFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return;
    }

    csvFile << ",";
    for (const std::string& terminal : terminals) {
        csvFile << terminal << ",";
    }
    csvFile << std::endl;

    for (NonTerminal* nonTerminal : nonTerminals) {
        csvFile << nonTerminal->getName() << ",";
        for (const std::string& terminal : terminals) {
            auto entry = parsingTable.find({nonTerminal, terminal});
            if (entry != parsingTable.end()) {
                auto& value = entry->second;
                std::string visibleProduction = "--> ";
                for (const std::shared_ptr<Symbol>& symbol : entry->second.getProduction()){
                    visibleProduction += symbol->getName() + " ";
                }
                csvFile << (value.isEpsilon() ? "epsilon" : (value.isSync() ? "sync" : visibleProduction)) << ",";
            } else {
                // No entry for the combination of non-terminal and terminal
                csvFile << "N/A,";
            }
        }
        csvFile << std::endl;
    }

    csvFile.close();
}
