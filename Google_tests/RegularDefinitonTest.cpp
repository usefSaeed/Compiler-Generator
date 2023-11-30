//
// Created by Meniem on 30-Nov-23.
//

#include "gtest/gtest.h"
#include "../RulesParser/RegularDefinition.h"

TEST(StandardizeRegex, WorksAsExpected){
    RegularDefinition regularDefinition("test", "digit (a-z | 0 - 9) digit+");

    regularDefinition.standardizeRegex();

    std::string result = "digit ((a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z) | (0|1|2|3|4|5|6|7|8|9)) digit+";

    ASSERT_EQ(regularDefinition.getRegex(), result);
}
