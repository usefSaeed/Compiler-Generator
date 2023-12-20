//
// Created by Meniem on 19-Dec-23.
//

#ifndef COMPILER_NONTERMINAL_H
#define COMPILER_NONTERMINAL_H

#include <string>
#include <vector>

class NonTerminal {
    private:
        std::string name;
        std::vector<std::vector<std::string>> productions;
    public:
        NonTerminal(std::string name, const std::vector<std::vector<std::string>> &productions);
        [[nodiscard]] std::string toString() const;
        [[nodiscard]] const std::string &getName() const;
        [[nodiscard]] const std::vector<std::vector<std::string>> &getProductions() const;


};


#endif //COMPILER_NONTERMINAL_H
