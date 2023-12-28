//
// Created by usef on 12/25/2023.
//

#include "ParserSet.h"

#include "../GrammarParser//Grammar.h"


void ParserSet::add(Terminal* t) {
    set.insert(t);
}

void ParserSet::addAll(const std::shared_ptr<ParserSet>& s){
    set.insert(s->set.begin(),s->set.end());
}

void ParserSet::removeEpsilon() {
    set.erase(Grammar::epsilon);
}

int ParserSet::getSize() {
    return set.size();
}

const std::unordered_set<Terminal *> &ParserSet::getSet() const {
    return set;
}

void ParserSet::clear() {
    set.clear();
}







