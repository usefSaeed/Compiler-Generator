//
// Created by usef on 12/26/2023.
//

#include "FirstSetsGenerator.h"




void FirstSetsGenerator::exec() {
    unsigned long long size = nts.size();
    size--;
    for (int i=size; i>=0; i--) {
        nts[i]->computeFirst();
        showFirstSet(nts[i]);
    }
}

void FirstSetsGenerator::showFirstSet(const std::shared_ptr<NonTerminal>& nt) {
    std::cout << "FIRST( " << nt->getName() << " ) = " << nt->getFirstSet().get() << "\n";
}

FirstSetsGenerator::FirstSetsGenerator(std::vector<std::shared_ptr<NonTerminal>> nts) {
    this->nts = std::move(nts);
    exec();
}

const std::vector<std::shared_ptr<NonTerminal>> &FirstSetsGenerator::getNTsWithFirstSets() const {
    return nts;
}

