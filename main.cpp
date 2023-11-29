#include <iostream>
#include "RulesParser/RulesConverter.h"

int main(int argc, char *argv[]) {

    RulesConverter rulesConverter("../Rules.txt");
    rulesConverter.ParseFile();

    return 0;
}