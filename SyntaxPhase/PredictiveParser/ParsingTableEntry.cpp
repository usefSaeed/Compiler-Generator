//
// Created by deffo on 24/12/23.
//

#include "ParsingTableEntry.h"

#include <utility>

ParsingTableEntry::ParsingTableEntry() = default;

ParsingTableEntry::ParsingTableEntry(std::string type) {
    if (type == "sync"){
        this->sync = true;
    } else if ( type == "epsilon"){
        this->epsilon = true;
    }
}

ParsingTableEntry::ParsingTableEntry(std::vector<std::vector<std::shared_ptr<Symbol>>> productions) {
    this->productions = std::move(productions);
}

bool ParsingTableEntry::isSync() const {
    return this->sync;
}

bool ParsingTableEntry::isEpsilon() const {
    return this->epsilon;
}

std::vector<std::vector<std::shared_ptr<Symbol>>> ParsingTableEntry::getProductions() {
    return this->productions;
}

