//
// Created by deffo on 24/12/23.
//

#include "ParsingTableEntry.h"

ParsingTableEntry::ParsingTableEntry() = default;

ParsingTableEntry::ParsingTableEntry(std::string type) {
    if (type == "sync"){
        this->sync = true;
    } else if ( type == "epsilon"){
        this->epsilon = true;
    }
}

ParsingTableEntry::ParsingTableEntry(productionsVector productions) {
    this->productions = std::move(productions);
}

bool ParsingTableEntry::isSync() const {
    return this->sync;
}

bool ParsingTableEntry::isEpsilon() const {
    return this->epsilon;
}

productionsVector ParsingTableEntry::getProductions() {
    return this->productions;
}

