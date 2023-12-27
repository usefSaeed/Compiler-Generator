//
// Created by usef on 12/25/2023.
//

#ifndef COMPILER_PARSERSET_H
#define COMPILER_PARSERSET_H

#include "../Common/Terminal.h"
#include <unordered_set>
#include "memory"

class ParserSet{
    protected:
        std::unordered_set<Terminal*> set;
        void add(Terminal* t);
        void addAll(const std::shared_ptr<ParserSet>& s);
        void removeEpsilon();
};

#endif //COMPILER_PARSERSET_H
