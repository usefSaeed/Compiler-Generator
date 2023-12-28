//
// Created by usef on 12/26/2023.
//

#include "FollowSetsGenerator.h"
#include "FollowSet.h"


void FollowSetsGenerator::exec() {
    for (auto& nt : nts){
        if (nt->isFollowComputed())
            continue;
        getFollow(nt);
        showFollowSet(nt);
        nt->setFollowComputed();
        lockedNTs.clear();
    }
}

std::shared_ptr<FollowSet> FollowSetsGenerator::getFollow(NonTerminal* nt){
    if (nt==startSymbol)
        nt->getFollowSet()->addEOI();
    lockedNTs.insert(nt);
    for (auto& nt_checked : nts){
        for (auto& p : nt_checked->getProductions()){
            bool keepLooking = true;
            for (auto& s : p){
                if (!keepLooking)
                    keepLooking = nt->getFollowSet()->handleSymbol(s.get());
                if (s.get()==nt)
                    keepLooking = false;
            }
            if (!keepLooking && isNotLocked(nt_checked)) {
                lockedNTs.insert(nt_checked);
                nt->getFollowSet()->addFollowSubset(getFollow(nt_checked));
            }
        }
    }
    return nt->getFollowSet();
}

void FollowSetsGenerator::showFollowSet(NonTerminal* nt) {
    std::cout << "FOLLOW( " << nt->getName() << " ) = " << nt->getFollowSet().get() << "\n";
}

FollowSetsGenerator::FollowSetsGenerator(std::vector<NonTerminal*> nts, const NonTerminal* startSymbol) {
    this->nts = std::move(nts);
    this->startSymbol = startSymbol;
    exec();
}

std::vector<NonTerminal*> FollowSetsGenerator::getNTsWithFollowSets() {
    return nts;
}

bool FollowSetsGenerator::isNotLocked(NonTerminal* nt) {
    return !lockedNTs.contains(nt);
}
