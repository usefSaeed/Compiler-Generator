//
// Created by Meniem on 28-Nov-23.
//

#ifndef COMPILER_REGULARDEFINITION_H
#define COMPILER_REGULARDEFINITION_H

#include <string>
#include "../Util/Util.h"
#include <utility>
#include <iostream>
#include "algorithm"

class RegularDefinition {
    private:
        std::string name;
        std::string regex;
        static void enumerateRanges(std::string& str);
        static void replaceDefinitions(std::string& str, std::vector<RegularDefinition> regularDefinitions);

    public:
        RegularDefinition();
        RegularDefinition(std::string name, std::string regex);

        [[nodiscard]] const std::string &getName() const;
        [[nodiscard]] const std::string &getRegex() const;
        void standardizeRegex(std::vector<RegularDefinition> regularDefinitions);
};

#endif //COMPILER_REGULARDEFINITION_H
