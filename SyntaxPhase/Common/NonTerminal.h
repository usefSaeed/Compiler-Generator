//
// Created by Meniem on 24-Dec-23.
//

#ifndef COMPILER_NONTERMINAL_H
#define COMPILER_NONTERMINAL_H


#include "Symbol.h"
#include <vector>

class NonTerminal : public Symbol {
public:
    explicit NonTerminal(const std::string &name);

public:
    [[nodiscard]] const std::vector<std::vector<Symbol>> &getProductions() const;

    void setProductions(const std::vector<std::vector<Symbol>> &productionsVector);

private:
    std::vector<std::vector<Symbol>> productions;
};




#endif //COMPILER_NONTERMINAL_H
