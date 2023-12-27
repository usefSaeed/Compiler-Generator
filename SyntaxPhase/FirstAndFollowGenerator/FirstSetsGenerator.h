//
// Created by usef on 12/26/2023.
//

#ifndef COMPILER_FIRSTSETSGENERATOR_H
#define COMPILER_FIRSTSETSGENERATOR_H

#include "../Common/NonTerminal.h"

#include <utility>
#include "iostream"

class FirstSetsGenerator{
private:
    std::vector<std::shared_ptr<NonTerminal>> nts;
    static void showFirstSet(const std::shared_ptr<NonTerminal>& nt);
    void exec();

public:
    [[nodiscard]] const std::vector<std::shared_ptr<NonTerminal>> &getNTsWithFirstSets() const;

public:
    explicit FirstSetsGenerator(std::vector<std::shared_ptr<NonTerminal>> nts);

};

#endif //COMPILER_FIRSTSETSGENERATOR_H
