//
// Created by Meniem on 24-Dec-23.
//

#include "NonTerminal.h"
NonTerminal::NonTerminal(const std::string &name) : Symbol(name, false) {}

const std::vector<std::vector<std::shared_ptr<Symbol>>> &NonTerminal::getProductions() const {
    return productions;
}

void NonTerminal::setProductions(const std::vector<std::vector<std::shared_ptr<Symbol>>> &productionsVector) {
    NonTerminal::productions = productionsVector;
}

std::string NonTerminal::toString() const {
    std::string result = "Name: " + this->getName() + " Productions: ";

    for (const auto& production : productions) {
        for (const auto& symbol : production) {
            result += symbol->getName() + " ";
        }
        result.pop_back(); // Remove the extra space
        result += " | ";
    }
    result.erase(result.length()-2);

    return result;
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
