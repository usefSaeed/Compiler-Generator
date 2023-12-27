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
        std::vector<std::vector<std::shared_ptr<Symbol>>> productions;

    public:
        ParsingTableEntry();
        explicit ParsingTableEntry(std::string type);
        explicit ParsingTableEntry(std::vector<std::vector<std::shared_ptr<Symbol>>> productions);
        [[nodiscard]] bool isSync() const;
        [[nodiscard]] bool isEpsilon() const;
        std::vector<std::vector<std::shared_ptr<Symbol>>> getProductions();

};


#endif //COMPILER_PARSINGTABLEENTRY_H
