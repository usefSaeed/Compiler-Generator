//
// Created by Meniem on 19-Dec-23.
//

#ifndef COMPILER_GRAMMARCONVERTER_H
#define COMPILER_GRAMMARCONVERTER_H

#include <string>
#include <unordered_set>
#include "NonTerminal.h"

class GrammarConverter {
    private:
    static int definitionCounter;
    std::vector<NonTerminal> nonTerminals;
    std::unordered_set<std::string> nonTerminalNames;
    std::unordered_set<std::string> terminals;
    [[nodiscard]] static bool hasImmediateLeftRecursion(const NonTerminal& nonTerminal);
    [[nodiscard]] static NonTerminal substitute(const NonTerminal& currentNonTerminal, const NonTerminal& potentiallySubstitutedNonTerminal);
    [[nodiscard]] static std::vector<NonTerminal> eliminateImmediateLeftRecursion(const NonTerminal& nonTerminal);

    public:
        GrammarConverter();

        [[nodiscard]] int parseFile(const std::string& filePath);
        [[nodiscard]] const std::vector<NonTerminal> &getNonTerminals() const;
        [[nodiscard]] const std::unordered_set<std::string> &getTerminals() const;
        [[nodiscard]] int validateGrammar(const std::string& definition);
        [[nodiscard]] int findTerminals(std::string& productions);
        [[nodiscard]] int parseProductions(const std::string& nonTerminalName, std::string& productions);
        [[nodiscard]] bool leftFactor();
        [[nodiscard]] bool eliminateLeftRecursion();
};


#endif //COMPILER_GRAMMARCONVERTER_H
