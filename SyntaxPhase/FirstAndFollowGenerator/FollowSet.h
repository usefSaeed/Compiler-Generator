//
// Created by usef on 12/25/2023.
//

#ifndef COMPILER_FIRSTSET_H
#define COMPILER_FIRSTSET_H

#include "ParserSet.h"

#include "iostream"


class FollowSet : public ParserSet {
private:

public:
    friend std::ostream& operator<<(std::ostream& os, const FollowSet* fs);

};

#endif //COMPILER_FIRSTSET_H
