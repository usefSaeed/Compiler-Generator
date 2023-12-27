//
// Created by usef on 12/26/2023.
//

#ifndef COMPILER_FIRSTSETSGENERATOR_H
#define COMPILER_FIRSTSETSGENERATOR_H

#include "../Common/NonTerminal.h"

#include <utility>
#include "unordered_set"
#include "iostream"

class FollowSetsGenerator{
private:
    std::vector<NonTerminal> nts;
    const NonTerminal* startSymbol;
    static void showFollowSet(NonTerminal nt);
    std::unordered_set<NonTerminal*> lockedNTs;
    void exec();


public:
    explicit FollowSetsGenerator(std::vector<NonTerminal> nts, const NonTerminal* startSymbol);
    [[nodiscard]] std::vector<NonTerminal> getNTsWithFollowSets();

};

#endif //COMPILER_FIRSTSETSGENERATOR_H
