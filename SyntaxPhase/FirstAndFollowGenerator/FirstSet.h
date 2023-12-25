//
// Created by usef on 12/25/2023.
//

#ifndef COMPILER_FIRSTSET_H
#define COMPILER_FIRSTSET_H

#include <unordered_set>
#include "../Common/Terminal.h"
#include "ParserSet.h"

class FirstSet : ParserSet {
    private:
        [[nodiscard]] bool hasEpsilon();
        void addEpsilon();
};

#endif //COMPILER_FIRSTSET_H
