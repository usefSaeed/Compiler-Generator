//
// Created by usef on 12/26/2023.
//

#include "FollowSetsGenerator.h"
#include "FollowSet.h"


void FollowSetsGenerator::exec() {
    for (auto& nt : nts){
        if (nt.isFollowComputed())
            continue;
        FollowSet* fs = nt.getFollowSet().get();
        if (&nt==startSymbol)
            fs->addEOI();
        lockedNTs.insert(&nt);
        //LOOP
        nt.setFollowComputed();
    }
}

void FollowSetsGenerator::showFollowSet(NonTerminal nt) {
    std::cout << "FIRST( " << nt.getName() << " ) = " << nt.getFirstSet().get() << "\n";
}

FollowSetsGenerator::FollowSetsGenerator(std::vector<NonTerminal> nts, const NonTerminal* startSymbol) {
    this->nts = std::move(nts);
    this->startSymbol = startSymbol;
    exec();
}

std::vector<NonTerminal> FollowSetsGenerator::getNTsWithFollowSets() {
    return nts;
}
