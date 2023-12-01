#include <iostream>
#include "RulesParser/RulesConverter.h"

int main(int argc, char *argv[]) {

    if (argc != 2){
        std::cerr << "Wrong number of parameter (One argument required: Rules File Path)" << "\n";
        return -1;
    }

    RulesConverter rulesConverter(argv[1]);
    int statusCode = rulesConverter.parseFile();
    if (statusCode == -1){
        std::cerr << "Badly Formatted Rules File" << "\n";
        return -1;
    }

    std::vector<RegularExpression> regularExpressions = rulesConverter.getRegularExpressions();

    for (const RegularExpression& regExp : regularExpressions) {
        std::cout << regExp.toString() << "\n";
    }

    return 0;
}