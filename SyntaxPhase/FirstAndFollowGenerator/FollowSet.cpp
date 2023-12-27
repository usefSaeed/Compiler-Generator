//
// Created by usef on 12/25/2023.
//

#include "FollowSet.h"

Terminal* FollowSet::EOI = new Terminal("$");

std::ostream &operator<<(std::ostream &os, const FollowSet* fs) {
    os << "{ ";int i = 0;int limit = fs->set.size()-1;
    for (const auto t : fs->set) {
        os << t;
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

FollowSet::FollowSet() = default;
