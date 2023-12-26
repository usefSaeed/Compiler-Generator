//
// Created by usef on 12/26/2023.
//

#include "FirstSetsGenerator.h"

#include <utility>
#include "iostream"


void FirstSetsGenerator::exec() {
    unsigned long long size = nts.size();
    size--;
    for (int i=size; i>=0; i--) {
        nts[i].computeFirst();
        showSet(nts[i]);
    }
}

void FirstSetsGenerator::showSet(NonTerminal nt) {
    std::cout << "FIRST( " << nt.getName() << " ) = " << nt.getFirstSet().get() << "\n";
}

FirstSetsGenerator::FirstSetsGenerator(std::vector<NonTerminal> nts) {
    this->nts = std::move(nts);
    exec();
}

std::vector<NonTerminal> FirstSetsGenerator::getNTsWithFirstSets() {
    return nts;
}
