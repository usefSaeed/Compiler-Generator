#include <iostream>
#include <vector>
#include "util.h"
#include "RulesParser/regularDefinition.h"
#include "RulesParser/regularExpression.h"

int main() {
    std::vector<std::string> words = split("This is a test string.", ' ');
    for (const std::string& word : words)
        std::cout << word << "\n";

    words = splitWithStringDelimiter("A => A + B  B => B + C  C => C + D", "=>");
    for (const std::string& word : words)
        std::cout << word << "\n";

    regularDefinition regDef("digit", "0-9");
    std::cout << "Name: " << regDef.getName() << "\n";
    std::cout << "Regex: " << regDef.getRegex() << "\n";
    regDef.standardizeRegex();
    std::cout << "Regex: " << regDef.getRegex() << "\n";


    regularExpression regExp("Id", "letter (letter | digit)*", 3);
    std::cout << "Name: " << regExp.getName() << "\n";
    std::cout << "Regex: " << regExp.getRegex() << "\n";
    std::cout << "Priority: " << regExp.getPriority() << "\n";
    regExp.standardizeRegex();
    std::cout << "Regex: " << regExp.getRegex() << "\n";

    return 0;
}