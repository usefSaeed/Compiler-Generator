//
// Created by Meniem on 24-Dec-23.
//

#ifndef COMPILER_NONTERMINAL_H
#define COMPILER_NONTERMINAL_H


#include "Symbol.h"
#include "Terminal.h"
#include <vector>
#include <memory>

class NonTerminal : public Symbol {
public:
    explicit NonTerminal(const std::string &name);

public:
    friend std::ostream& operator<<(std::ostream& os, const NonTerminal& nt);
    [[nodiscard]] const std::vector<std::vector<std::shared_ptr<Symbol>>> &getProductions() const;
    [[nodiscard]] const std::unordered_set<Terminal*> &getFollowSet() const;
    [[nodiscard]] const std::unordered_set<Terminal*> &getFirstSet() const;
    [[nodiscard]] std::string toString() const;
    void setProductions(const std::vector<std::vector<std::shared_ptr<Symbol>>> &productionsVector);

private:
    std::vector<std::vector<std::shared_ptr<Symbol>>> productions;
    std::unordered_set<Terminal*> followSet;
    std::unordered_set<Terminal*> firstSet;
};




#endif //COMPILER_NONTERMINAL_H
