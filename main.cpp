#include <iostream>
#include "RulesParser/RegularDefinition.h"
#include "RulesParser/RegularExpression.h"

int main() {

    RegularDefinition regDef("digit", "0-9");
    std::cout << "Name: " << regDef.getName() << "\n";
    std::cout << "Regex: " << regDef.getRegex() << "\n";
    regDef.standardizeRegex();
    std::cout << "Regex: " << regDef.getRegex() << "\n";


    RegularExpression regExp("Id", "letter (letter | digit)*", 3);
    std::cout << "Name: " << regExp.getName() << "\n";
    std::cout << "Regex: " << regExp.getRegex() << "\n";
    std::cout << "Priority: " << regExp.getPriority() << "\n";
    regExp.standardizeRegex();
    std::cout << "Regex: " << regExp.getRegex() << "\n";


    return 0;
}