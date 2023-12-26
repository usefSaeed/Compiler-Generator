//
// Created by usef on 12/26/2023.
//

#ifndef COMPILER_FIRSTSETSGENERATOR_H
#define COMPILER_FIRSTSETSGENERATOR_H

#include "../Common/NonTerminal.h"


class FirstSetsGenerator{
private:
    std::vector<NonTerminal> nts;
    static void showSet(NonTerminal nt);

public:
    explicit FirstSetsGenerator(std::vector<NonTerminal> nts);
    void exec();

};

#endif //COMPILER_FIRSTSETSGENERATOR_H
