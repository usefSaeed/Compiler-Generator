//
// Created by Meniem on 19-Dec-23.
//

#ifndef COMPILER_GRAMMARCONVERTER_H
#define COMPILER_GRAMMARCONVERTER_H

#include <string>
#include <unordered_set>
#include "NonTerminalSymbol.h"

class GrammarConverter {
    private:
    static int definitionCounter;
    std::vector<NonTerminalSymbol> nonTerminals;
    std::unordered_set<std::string> nonTerminalNames;
    std::unordered_set<std::string> terminals;
    [[nodiscard]] static bool hasImmediateLeftRecursion(const NonTerminalSymbol& nonTerminal);
    [[nodiscard]] static NonTerminalSymbol substitute(const NonTerminalSymbol& currentNonTerminal, const NonTerminalSymbol& potentiallySubstitutedNonTerminal);
    [[nodiscard]] static std::vector<NonTerminalSymbol> eliminateImmediateLeftRecursion(const NonTerminalSymbol& nonTerminal);

    public:
        GrammarConverter();
        [[nodiscard]] int parseFile(const std::string& filePath);
        [[nodiscard]] const std::vector<NonTerminalSymbol> &getNonTerminals() const;
        [[nodiscard]] const std::unordered_set<std::string> &getTerminals() const;
        [[nodiscard]] int validateGrammar(const std::string& definition);
        [[nodiscard]] int findTerminals(std::string& productions);
        [[nodiscard]] int parseProductions(const std::string& nonTerminalName, std::string& productions);
        [[nodiscard]] bool leftFactor();
        [[nodiscard]] bool eliminateLeftRecursion();
};


#endif //COMPILER_GRAMMARCONVERTER_H
