//
// Created by Meniem on 24-Dec-23.
//

#ifndef COMPILER_NONTERMINAL_H
#define COMPILER_NONTERMINAL_H


#include "Symbol.h"
#include <vector>
#include <memory>

class NonTerminal : public Symbol {
public:
    explicit NonTerminal(const std::string &name);

public:
    [[nodiscard]] const std::vector<std::vector<std::shared_ptr<Symbol>>> &getProductions() const;
    [[nodiscard]] std::string toString() const;
    void setProductions(const std::vector<std::vector<std::shared_ptr<Symbol>>> &productionsVector);

private:
    std::vector<std::vector<std::shared_ptr<Symbol>>> productions;
};




#endif //COMPILER_NONTERMINAL_H
