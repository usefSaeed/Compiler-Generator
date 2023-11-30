#include <iostream>
#include "RulesParser/RulesConverter.h"

int main(int argc, char *argv[]) {

    RulesConverter rulesConverter("../Rules.txt");
    rulesConverter.parseFile();

    std::vector<RegularExpression> regularExpressions = rulesConverter.getRegularExpressions();

    for (const RegularExpression& regExp : regularExpressions) {
        std::cout << regExp.toString() << "\n";
    }

    return 0;
}