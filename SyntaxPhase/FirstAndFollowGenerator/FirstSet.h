//
// Created by usef on 12/25/2023.
//

#ifndef COMPILER_FIRSTSET_H
#define COMPILER_FIRSTSET_H

#include <unordered_set>
#include "../Common/Terminal.h"
#include "ParserSet.h"

class FirstSet : public ParserSet {
private:
    [[nodiscard]] bool hasNoEpsilon();

public:
    void addEpsilon();
    bool handleSymbol(Symbol* s);
    friend std::ostream& operator<<(std::ostream& os, const FirstSet* fs);

};

#endif //COMPILER_FIRSTSET_H
