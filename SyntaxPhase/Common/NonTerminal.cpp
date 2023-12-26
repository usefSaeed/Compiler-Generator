//
// Created by Meniem on 24-Dec-23.
//

#include "NonTerminal.h"

NonTerminal::NonTerminal(const std::string &name) : Symbol(name, false) {
    firstSet = nullptr;
    followSet = nullptr;
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

FirstSet* NonTerminal::getFirstSet() {
    if (isFirstComputed())
        return firstSet;
    computeFirst();
    return firstSet;
}

void NonTerminal::computeFirst() {
    firstSet = new FirstSet();
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

bool NonTerminal::isFirstComputed() {
    return firstSet!= nullptr;
}

