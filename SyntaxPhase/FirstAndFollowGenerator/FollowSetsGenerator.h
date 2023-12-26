//
// Created by usef on 12/26/2023.
//

#ifndef COMPILER_FIRSTSETSGENERATOR_H
#define COMPILER_FIRSTSETSGENERATOR_H

#include "../Common/NonTerminal.h"


class FollowSetsGenerator{
private:
    std::vector<NonTerminal> nts;
    static void showSet(NonTerminal nt);
    void exec();


public:
    explicit FollowSetsGenerator(std::vector<NonTerminal> nts);
    [[nodiscard]] std::vector<NonTerminal> getNTsWithFollowSets();

};

#endif //COMPILER_FIRSTSETSGENERATOR_H
