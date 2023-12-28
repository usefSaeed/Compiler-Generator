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

std::shared_ptr<FollowSet> FollowSetsGenerator::getFollow(const std::shared_ptr<NonTerminal>& nt){
    if (nt.get()==startSymbol)
        nt->getFollowSet()->addEOI();
    lockedNTs.insert(nt);
    for (auto& nt_checked : nts){
        for (auto& p : nt_checked->getProductions()){
            bool keepLooking = true;
            for (auto& s : p){
                if (!keepLooking)
                    keepLooking = nt->getFollowSet()->handleSymbol(s.get());
                if (s==nt)
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

void FollowSetsGenerator::showFollowSet(const std::shared_ptr<NonTerminal>& nt) {
    std::cout << "FOLLOW( " << nt->getName() << " ) = " << nt->getFollowSet().get() << "\n";
}

FollowSetsGenerator::FollowSetsGenerator(std::vector<std::shared_ptr<NonTerminal>> nts,const NonTerminal* startSymbol){
    this->nts = std::move(nts);
    this->startSymbol = startSymbol;
    exec();
}


bool FollowSetsGenerator::isNotLocked(const std::shared_ptr<NonTerminal>& nt) {
    return !lockedNTs.contains(nt);
}

const std::vector<std::shared_ptr<NonTerminal>> &FollowSetsGenerator::getNTsWithFollowSets() const {
    return nts;
}
