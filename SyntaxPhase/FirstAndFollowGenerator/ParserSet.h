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

public:
    virtual bool handleSymbol(Symbol* s) = 0;
    int getSize();
    void add(Terminal* t);
    const std::unordered_set<Terminal *> &getSet() const;
    void clear();
    void addAll(const std::shared_ptr<ParserSet>& s);
    void removeEpsilon();
};

#endif //COMPILER_PARSERSET_H
