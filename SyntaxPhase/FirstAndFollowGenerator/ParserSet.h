//
// Created by usef on 12/25/2023.
//

#ifndef COMPILER_PARSERSET_H
#define COMPILER_PARSERSET_H

#include "../Common/Terminal.h"
#include <unordered_set>

class ParserSet{
    protected:
        std::unordered_set<Terminal*> set;
        [[nodiscard]] bool isComputed();
        void add(Terminal* t);
        void addAll(const ParserSet& s);
        void removeEpsilon();
public:

};

#endif //COMPILER_PARSERSET_H
