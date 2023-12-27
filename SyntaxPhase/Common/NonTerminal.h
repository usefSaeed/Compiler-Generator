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
private:
    std::vector<std::vector<std::shared_ptr<Symbol>>> productions;
    std::shared_ptr<FirstSet> firstSet;
    std::shared_ptr<FollowSet> followSet;
    bool followComputed;

public:
    explicit NonTerminal(const std::string &name);

    void computeFirst();
    void setFollowComputed();
    void setProductions(const std::vector<std::vector<std::shared_ptr<Symbol>>> &productionsVector);

    [[nodiscard]] bool isFollowComputed() const;
    [[nodiscard]] std::shared_ptr<FirstSet> getFirstSet();
    [[nodiscard]] std::shared_ptr<FollowSet> getFollowSet();
    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Symbol>>> getProductions() const;

    friend std::ostream& operator<<(std::ostream& os, const NonTerminal& nt);
};




#endif //COMPILER_NONTERMINAL_H
