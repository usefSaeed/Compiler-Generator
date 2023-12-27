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

bool ParserSet::handleSymbol(Symbol *s) {
    if (s->isTerminal()) {
        this->add(dynamic_cast<Terminal *> (s));
        return true;
    }
    NonTerminal* nt = dynamic_cast<NonTerminal *> (s);
    bool hasEpsilonAlready = !nt->getFirstSet()->hasNoEpsilon();
    this->addAll(nt->getFirstSet());
    if (nt->getFirstSet()->hasNoEpsilon() || hasEpsilonAlready)
        return true;
    this->removeEpsilon();
    return false;
}






