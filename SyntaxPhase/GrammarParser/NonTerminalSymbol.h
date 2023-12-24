//
// Created by Meniem on 19-Dec-23.
//

#ifndef COMPILER_NONTERMINALSYMBOL_H
#define COMPILER_NONTERMINALSYMBOL_H

#include <string>
#include <vector>

typedef std::vector<std::vector<std::string>> productionsVector;

class NonTerminalSymbol {
    private:
        std::string name;
        productionsVector productions;
    public:
        NonTerminalSymbol(std::string name, productionsVector productions);
        [[nodiscard]] std::string toString() const;
        [[nodiscard]] const std::string &getName() const;
        [[nodiscard]] const productionsVector &getProductions() const;

    void setProductions(const productionsVector &productionsVector);
};


#endif //COMPILER_NONTERMINALSYMBOL_H
