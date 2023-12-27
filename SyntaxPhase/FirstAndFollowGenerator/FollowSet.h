//
// Created by usef on 12/25/2023.
//

#ifndef COMPILER_FOLLOWSET_H
#define COMPILER_FOLLOWSET_H

#include "ParserSet.h"

#include "iostream"


class FollowSet : public ParserSet {
private:

public:
    FollowSet();
    void addEOI();
    static Terminal* EOI;
    friend std::ostream& operator<<(std::ostream& os, const FollowSet* fs);

};

#endif //COMPILER_FOLLOWSET_H
