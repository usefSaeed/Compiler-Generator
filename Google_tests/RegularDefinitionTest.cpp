//
// Created by Meniem on 30-Nov-23.
//

#include "gtest/gtest.h"
#include "../RulesParser/RegularDefinition.h"
#include "../RulesParser/RegularExpression.h"

TEST(StandardizeRegex, HandlesRangeWithSpaces){
    RegularDefinition regularDefinition("test", "digit (a-z | 0 - 9) digit+");

    std::vector<RegularDefinition> regularDefinitions;

    int status = regularDefinition.standardizeRegex(regularDefinitions);

    std::string result = "digit ((a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z) | (0|1|2|3|4|5|6|7|8|9)) digit+";

    ASSERT_EQ(regularDefinition.getRegex(), result);
    ASSERT_EQ(status, 0);
}

TEST(StandardizeRegex, ThrowsWhenRangeOperatorIsWronglyUsed){
    RegularDefinition regularDefinition("test", "ray (0-)");

    std::vector<RegularDefinition> regularDefinitions;

    int status = regularDefinition.standardizeRegex(regularDefinitions);

    ASSERT_EQ(status, -1);
}

TEST(StandardizeRegex, HandlesRecursiveRegularDefinitions){
    RegularDefinition regularDefinition("digit", "0-9");
    std::vector<RegularDefinition> regularDefinitions = {};
    int status = regularDefinition.standardizeRegex(regularDefinitions);

    regularDefinitions = {regularDefinition};
    RegularDefinition regularDefinition2("test", "digit+ anything");
    int status2= regularDefinition2.standardizeRegex(regularDefinitions);

    std::string result = "(0|1|2|3|4|5|6|7|8|9)+ anything";

    ASSERT_EQ(regularDefinition2.getRegex(), result);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(status2, 0);
}

TEST(StandardizeRegex, HandlesRecursiveRegularDefinitions2){
    RegularDefinition regularDefinition("digit", "0-9");
    std::vector<RegularDefinition> regularDefinitions = {};
    int status = regularDefinition.standardizeRegex(regularDefinitions);

    regularDefinitions = {regularDefinition};
    RegularDefinition regularDefinition2("digits", "digit+");
    int status2 = regularDefinition2.standardizeRegex(regularDefinitions);

    regularDefinitions = {regularDefinition, regularDefinition2};
    RegularDefinition regularDefinition3("num", "digit+ | digit+ . digits ( \\L | E digits)");
    int status3 = regularDefinition3.standardizeRegex(regularDefinitions);

    std::string result = "(0|1|2|3|4|5|6|7|8|9)+ | (0|1|2|3|4|5|6|7|8|9)+ . (0|1|2|3|4|5|6|7|8|9)+ ( \\L | E (0|1|2|3|4|5|6|7|8|9)+)";

    ASSERT_EQ(regularDefinition3.getRegex(), result);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(status2, 0);
    ASSERT_EQ(status3, 0);
}

TEST(StandardizeRegex, HandlesRecursiveRegularDefinitions3){
    RegularDefinition regularDefinition("digit", "0-9");
    std::vector<RegularDefinition> regularDefinitions = {};
    int status = regularDefinition.standardizeRegex(regularDefinitions);

    regularDefinitions = {regularDefinition};
    RegularDefinition regularDefinition2("letter", "a-z | A-Z");
    int status2 =regularDefinition2.standardizeRegex(regularDefinitions);

    regularDefinitions = {regularDefinition, regularDefinition2};
    RegularExpression regularExpression("id", "letter (letter|digit)*", 2);
    int status3 = regularExpression.standardizeRegex(regularDefinitions);

    std::string result = "(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z) | (A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z) ((a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z) | (A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)|(0|1|2|3|4|5|6|7|8|9))*";

    ASSERT_EQ(regularExpression.getRegex(), result);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(status2, 0);
    ASSERT_EQ(status3, 0);
}
