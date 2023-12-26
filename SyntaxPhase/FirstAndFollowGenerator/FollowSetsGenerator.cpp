//
// Created by usef on 12/26/2023.
//

#include "FollowSetsGenerator.h"

#include <utility>
#include "iostream"


void FollowSetsGenerator::exec() {

}

void FollowSetsGenerator::showSet(NonTerminal nt) {
    std::cout << "FIRST( " << nt.getName() << " ) = " << nt.getFirstSet().get() << "\n";
}

FollowSetsGenerator::FollowSetsGenerator(std::vector<NonTerminal> nts) {
    this->nts = std::move(nts);
    exec();
}

std::vector<NonTerminal> FollowSetsGenerator::getNTsWithFollowSets() {
    return nts;
}
