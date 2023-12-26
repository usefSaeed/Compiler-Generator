//
// Created by usef on 12/25/2023.
//

#include "FollowSet.h"
#include "iostream"
#include "../Common/Terminal.h"

std::ostream &operator<<(std::ostream &os, const FollowSet* fs) {
    os << "{ ";int i = 0;int limit = fs->set.size()-1;
    for (Terminal* t : fs->set) {
        os << t;
        if (i!=limit)
            os << ", ";
        i++;
    }
    os << " }";
    return os;
}
