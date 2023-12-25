//
// Created by Meniem on 24-Dec-23.
//

#ifndef COMPILER_GRAMMAR_H
#define COMPILER_GRAMMAR_H


#include <vector>
#include "../Common/NonTerminal.h"
#include "GrammarConverter.h"

class Grammar {
private :
    GrammarConverter modifiedGrammar;
    std::vector<NonTerminal> standardizedNonTerminals;
    NonTerminal* startSymbol = nullptr;

public:
    NonTerminal *getStartSymbol() const;
    const std::vector<NonTerminal> &getStandardizedNonTerminals() const;
    void standardizeNonTerminals();

public:
    explicit Grammar(GrammarConverter modifiedGrammar);
};


#endif //COMPILER_GRAMMAR_H
