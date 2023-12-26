//
// Created by Meniem on 24-Dec-23.
//

#ifndef COMPILER_NONTERMINAL_H
#define COMPILER_NONTERMINAL_H


#include "Symbol.h"
#include "../FirstAndFollowGenerator/FirstSet.h"
#include "../FirstAndFollowGenerator/FollowSet.h"

#include <vector>
#include <memory>
#include <unordered_set>

class NonTerminal : public Symbol {
public:
    explicit NonTerminal(const std::string &name);

public:
    friend std::ostream& operator<<(std::ostream& os, const NonTerminal& nt);
    [[nodiscard]] const std::vector<std::vector<std::shared_ptr<Symbol>>> &getProductions() const;
    std::shared_ptr<FirstSet> getFirstSet();
    void computeFirst();
    void setProductions(const std::vector<std::vector<std::shared_ptr<Symbol>>> &productionsVector);

private:
    std::vector<std::vector<std::shared_ptr<Symbol>>> productions;
    std::shared_ptr<FirstSet> firstSet;
//    std::shared_ptr<FollowSet> followSet;
};




#endif //COMPILER_NONTERMINAL_H
