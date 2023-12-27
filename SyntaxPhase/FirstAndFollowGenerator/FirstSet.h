//
// Created by usef on 12/25/2023.
//

#ifndef COMPILER_FIRSTSET_H
#define COMPILER_FIRSTSET_H


#include "ParserSet.h"

#include <unordered_set>

class FirstSet : public ParserSet {

public:
    void addEpsilon();

    [[nodiscard]] bool isComputed();
    [[nodiscard]] bool hasNoEpsilon();

    friend std::ostream& operator<<(std::ostream& os, const FirstSet* fs);
};

#endif //COMPILER_FIRSTSET_H
