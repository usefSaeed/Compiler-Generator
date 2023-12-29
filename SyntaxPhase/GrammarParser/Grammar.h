//
// Created by Meniem on 24-Dec-23.
//

#ifndef COMPILER_GRAMMAR_H
#define COMPILER_GRAMMAR_H


#include "../Common/NonTerminal.h"
#include "../Common/Terminal.h"
#include "GrammarConverter.h"

#include <vector>
#include <utility>
#include <unordered_map>
#include <memory>
#include <iostream>

class Grammar {
private :

    GrammarConverter modifiedGrammar;
    std::vector<std::shared_ptr<NonTerminal>> standardizedNonTerminals;
    NonTerminal* startSymbol = nullptr;
public:
    NonTerminal *getStartSymbol() const;

public:
    const std::vector<std::shared_ptr<NonTerminal>> &getStandardizedNonTerminals() const;
    friend std::ostream& operator<<(std::ostream& os, const Grammar& g);
    void standardizeNonTerminals();
    explicit Grammar(GrammarConverter modifiedGrammar);
    static Terminal* epsilon;

    // for debugging purposes
    explicit Grammar(){};
};


#endif //COMPILER_GRAMMAR_H
