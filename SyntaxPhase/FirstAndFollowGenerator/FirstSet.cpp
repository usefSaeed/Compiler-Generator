//
// Created by usef on 12/25/2023.
//

#include "FirstSet.h"

#include "../GrammarParser//Grammar.h"

bool FirstSet::hasNoEpsilon() {
    return !set.contains(Grammar::epsilon);
}

void FirstSet::addEpsilon() {
    this->add(Grammar::epsilon);
}

std::ostream &operator<<(std::ostream &os, const FirstSet* fs) {
    os << "{ ";int i = 0;int limit = fs->set.size()-1;
    for (const auto& t : fs->set) {
        os << t;
        if (i!=limit)
            os << ", ";
        i++;
    }
    os << " }";
    return os;
}

bool FirstSet::isComputed() {
    return !set.empty();
}
