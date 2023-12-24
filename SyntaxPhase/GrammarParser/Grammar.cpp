//
// Created by Meniem on 24-Dec-23.
//

#include "Grammar.h"
#include "../Common/Terminal.h"
#include <utility>
#include <unordered_map>
#include <memory>

void Grammar::standardizeNonTerminals() {
    auto terminalsSet = modifiedGrammar.getTerminals();
    auto oldNonTerminals = modifiedGrammar.getNonTerminals();
    std::unordered_map<std::string, std::shared_ptr<NonTerminal>>  nonTerminalMap;
    std::unordered_map<std::string, std::shared_ptr<Terminal>>  TerminalMap;

    for (const auto& nonTerminal : oldNonTerminals){
        auto productions = nonTerminal.getProductions();
        std::vector<std::vector<Symbol>> newProductions;
        for (const auto& production : productions){
            std::vector<Symbol> newProduction;
            for (auto symbolName : production){
                // Terminal
                if (terminalsSet.contains(symbolName)){
                    // not defined before
                    if (!TerminalMap.contains(symbolName)){
                        std::shared_ptr<Terminal> terminal = std::make_shared<Terminal>(symbolName);
                        TerminalMap.insert({symbolName, terminal});
                        newProduction.push_back(*terminal);
                    }
                    // defined before
                    else {
                        std::shared_ptr<Terminal> terminal = TerminalMap.find(symbolName)->second;
                        newProduction.push_back(*terminal);
                    }
                }
                // Non-Terminal
                else {
                    // not defined before
                    if (!nonTerminalMap.contains(symbolName)){
                        std::shared_ptr<NonTerminal> innerNonTerminal = std::make_shared<NonTerminal>(symbolName);
                        nonTerminalMap.insert({symbolName, innerNonTerminal});
                        newProduction.push_back(*innerNonTerminal);
                    }
                        // defined before
                    else {
                        std::shared_ptr<NonTerminal> innerNonTerminal = nonTerminalMap.find(symbolName)->second;
                        newProduction.push_back(*innerNonTerminal);
                    }
                }
            }
            newProductions.push_back(newProduction);
        }
        // not defined before
        if (!nonTerminalMap.contains(nonTerminal.getName())){
            std::shared_ptr<NonTerminal> outerNonTerminal = std::make_shared<NonTerminal>(nonTerminal.getName());
            outerNonTerminal->setProductions(newProductions);
            nonTerminalMap.insert({nonTerminal.getName(), outerNonTerminal});
            standardizedModifiedGrammar.push_back(*outerNonTerminal);
        }
        // defined before
        else {
            std::shared_ptr<NonTerminal> outerNonTerminal = nonTerminalMap.find(nonTerminal.getName())->second;
            outerNonTerminal->setProductions(newProductions);
            standardizedModifiedGrammar.push_back(*outerNonTerminal);
        }
    }

}

Grammar::Grammar(GrammarConverter modifiedGrammar) : modifiedGrammar(std::move(modifiedGrammar)) {}

const std::vector<NonTerminal> &Grammar::getStandardizedModifiedGrammar() const {
    return standardizedModifiedGrammar;
}
