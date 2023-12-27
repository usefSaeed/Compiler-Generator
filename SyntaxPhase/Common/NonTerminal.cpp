//
// Created by Meniem on 24-Dec-23.
//

#include "NonTerminal.h"

NonTerminal::NonTerminal(const std::string &name) : Symbol(name, false) {
    firstSet = std::make_shared<FirstSet>();
    followSet = std::make_shared<FollowSet>();
    followComputed = false;
}

const std::vector<std::vector<std::shared_ptr<Symbol>>> &NonTerminal::getProductions() const {
    return productions;
}

void NonTerminal::setProductions(const std::vector<std::vector<std::shared_ptr<Symbol>>> &productionsVector) {
    NonTerminal::productions = productionsVector;
}

std::ostream &operator<<(std::ostream &os, const NonTerminal &nt) {
    os << nt.getName() << " --> ";
    for (int i=0;i<nt.getProductions().size();i++){
        for (const auto& symbol : nt.getProductions()[i]){
            os << symbol->getName() << " ";
        }
        if (i<nt.getProductions().size()-1){
            os << "| ";
        }
    }
    os << std::endl;
    return os;
}

std::shared_ptr<FirstSet> NonTerminal::getFirstSet() {
    if (firstSet->isComputed())
        return firstSet;
    computeFirst();
    return firstSet;
}

void NonTerminal::computeFirst() {
    if (firstSet->isComputed())
        return;
    for (const auto& p : productions){
        int symbolIdx=0;
        while(symbolIdx < p.size()){
            bool isComplete = firstSet->handleSymbol(p[symbolIdx].get());
            if (isComplete)
                break;
            symbolIdx++;
        }
        bool allProductionsHaveEpsilon = symbolIdx == p.size();
        if (allProductionsHaveEpsilon)
            firstSet->addEpsilon();
    }
}

std::shared_ptr<FollowSet> NonTerminal::getFollowSet() {
    return followSet;
}

void NonTerminal::setFollowComputed() {
    followComputed = true;
}

bool NonTerminal::isFollowComputed() const {
    return followComputed;
}
