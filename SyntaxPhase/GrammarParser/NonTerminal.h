//
// Created by Meniem on 19-Dec-23.
//

#ifndef COMPILER_NONTERMINAL_H
#define COMPILER_NONTERMINAL_H

#include <string>
#include <vector>

typedef std::vector<std::vector<std::string>> productionsVector;

class NonTerminal {
    private:
        std::string name;
        productionsVector productions;
    public:
        NonTerminal(std::string name, productionsVector productions);
        [[nodiscard]] std::string toString() const;
        [[nodiscard]] const std::string &getName() const;
        [[nodiscard]] const productionsVector &getProductions() const;

    void setProductions(const productionsVector &productionsVector);
};


#endif //COMPILER_NONTERMINAL_H
