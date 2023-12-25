//
// Created by Meniem on 24-Dec-23.
//

#include <unordered_set>
#include "NonTerminal.h"

NonTerminal::NonTerminal(const std::string &name) : Symbol(name, false) {}

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

std::unordered_set<Terminal> &NonTerminal::getFirstSet() {

}

void NonTerminal::computeFirst() {

}

