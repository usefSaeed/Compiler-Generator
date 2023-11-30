//
// Created by Meniem on 28-Nov-23.
//

#ifndef COMPILER_REGULARDEFINITION_H
#define COMPILER_REGULARDEFINITION_H

#include <string>
#include "../Util/Util.h"
#include <utility>
#include <iostream>

class RegularDefinition {
    private:
        std::string name;
        std::string regex;
        static void EnumerateRanges(std::string& str);
        static void ReplaceDefinitions(std::string& str);
    public:
        RegularDefinition();
        RegularDefinition(std::string name, std::string regex);

        [[nodiscard]] const std::string &getName() const;
        [[nodiscard]] const std::string &getRegex() const;
        void standardizeRegex();



};

#endif //COMPILER_REGULARDEFINITION_H
