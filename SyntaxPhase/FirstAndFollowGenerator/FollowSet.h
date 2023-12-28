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
    void addFollowSubset(const std::shared_ptr<FollowSet>& fss);
    bool handleSymbol(Symbol* s) override;
    friend std::ostream& operator<<(std::ostream& os, const FollowSet* fs);

};

#endif //COMPILER_FOLLOWSET_H
