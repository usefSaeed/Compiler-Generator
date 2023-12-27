//
// Created by deffo on 24/12/23.
//

#ifndef COMPILER_PARSINGTABLEENTRY_H
#define COMPILER_PARSINGTABLEENTRY_H

#include "Common.h"

class ParsingTableEntry {
    private:
        bool epsilon = false;
        bool sync = false;
        ProductionsVector productions;

    public:
        ParsingTableEntry();
        explicit ParsingTableEntry(std::string type);
        explicit ParsingTableEntry(ProductionsVector productions);
        [[nodiscard]] bool isSync() const;
        [[nodiscard]] bool isEpsilon() const;
        ProductionsVector getProductions();

};


#endif //COMPILER_PARSINGTABLEENTRY_H
