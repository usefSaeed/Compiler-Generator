//
// Created by usef on 12/25/2023.
//

#include "FollowSet.h"
#include "../Common/NonTerminal.h"

Terminal* FollowSet::EOI = new Terminal("$");

std::ostream &operator<<(std::ostream &os, const FollowSet* fs) {
    os << "{ ";int i = 0;int limit = fs->set.size()-1;
    for (const auto t : fs->set) {
        os << "'" << t << "'";
        if (i!=limit)
            os << ", ";
        i++;
    }
    os << " }";
    return os;
}

void FollowSet::addEOI() {
    this->add(EOI);
}

void FollowSet::addFollowSubset(const std::shared_ptr<FollowSet>& fss) {
    this->addAll(fss);
}

bool FollowSet::handleSymbol(Symbol *s) {
    if (s->isTerminal()) {
        auto* t =dynamic_cast<Terminal *> (s);
        if (!t->isEpsilon())
            this->add(t);
        return true;
    }
    auto* nt = dynamic_cast<NonTerminal *> (s);
    this->addAll(nt->getFirstSet());
    if (nt->getFirstSet()->hasNoEpsilon())
        return true;
    this->removeEpsilon();
    return false;
}

FollowSet::FollowSet() = default;
