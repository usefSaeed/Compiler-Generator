//
// Created by Meniem on 28-Nov-23.
//

#ifndef COMPILER_REGULARDEFINITION_H
#define COMPILER_REGULARDEFINITION_H

#include <string>
#include <vector>


class RegularDefinition {
    private:
        std::string name;
        std::string regex;
        [[nodiscard]] static int enumerateRanges(std::string& str);
        static void replaceDefinitions(std::string& str, std::vector<RegularDefinition> regularDefinitions);
        static void parenthesizeClosures(std::string& str);
        [[nodiscard]] static std::string parenthesizeDisjunctions(std::string& str);

public:
        RegularDefinition();
        RegularDefinition(std::string name, std::string regex);
        [[nodiscard]] const std::string &getName() const;
        [[nodiscard]] const std::string &getRegex() const;
        [[nodiscard]] int standardizeRegex(std::vector<RegularDefinition> regularDefinitions);
};

#endif //COMPILER_REGULARDEFINITION_H
