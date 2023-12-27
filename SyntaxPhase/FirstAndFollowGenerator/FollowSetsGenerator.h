//
// Created by usef on 12/26/2023.
//

#ifndef COMPILER_FOLLOWSETSGENERATOR_H
#define COMPILER_FOLLOWSETSGENERATOR_H

#include "../Common/NonTerminal.h"

#include <utility>
#include "unordered_set"
#include "iostream"

class FollowSetsGenerator{
private:
    std::vector<std::shared_ptr<NonTerminal>> nts;
    const NonTerminal* startSymbol;
    std::unordered_set<std::shared_ptr<NonTerminal>> lockedNTs;
    void exec();
    static void showFollowSet(const std::shared_ptr<NonTerminal>& nt);
    std::shared_ptr<FollowSet> getFollow(const std::shared_ptr<NonTerminal>& nt);

public:
    explicit FollowSetsGenerator(std::vector<std::shared_ptr<NonTerminal>> nts,const NonTerminal* startSymbol);

    [[nodiscard]] bool isNotLocked(const std::shared_ptr<NonTerminal>& nt);
    [[nodiscard]] const std::vector<std::shared_ptr<NonTerminal>> &getNTsWithFollowSets() const;

};

#endif //COMPILER_FOLLOWSETSGENERATOR_H
