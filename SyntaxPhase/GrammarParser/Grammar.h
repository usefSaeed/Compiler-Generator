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
    Terminal *getEpsilon() const;
    NonTerminal *getStartSymbol() const;
    friend std::ostream& operator<<(std::ostream& os, const Grammar& g);
    const std::vector<NonTerminal> &getStandardizedNonTerminals() const;
    void standardizeNonTerminals();
    void computeFirst();
    void showFirst();
    void computeFollow();
    explicit Grammar(GrammarConverter modifiedGrammar);

    static Terminal* epsilon;
};


#endif //COMPILER_GRAMMAR_H
