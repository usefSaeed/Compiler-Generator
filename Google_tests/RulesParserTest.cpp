//
// Created by Meniem on 29-Nov-23.
//

#include "gtest/gtest.h"
#include "../RulesParser/RulesConverter.h"

TEST(CheckType, RecognizesKeyWords){
    std::string str = "{boolean int float}";

    int type = RulesConverter::CheckType(str);

    ASSERT_EQ(type,RulesConverter::KEYWORDS);
}

TEST(CheckType, RecognizesPunctuation){
    std::string str = "[; , \\( \\) { }]";

    int type = RulesConverter::CheckType(str);

    ASSERT_EQ(type,RulesConverter::PUNCTUATION);
}

TEST(CheckType, RecognizesRegularDefiniton){
    std::string str = "digit = 0 - 9";

    int type = RulesConverter::CheckType(str);

    ASSERT_EQ(type,RulesConverter::REGULAR_DEFINITION);
}

TEST(CheckType, RecognizesRegularExpression){
    std::string str = "id: letter (letter|digit)*";

    int type = RulesConverter::CheckType(str);

    ASSERT_EQ(type,RulesConverter::REGULAR_EXPRESSION);
}

TEST(CheckType, RecognizesRegularExpressionHard){
    std::string str = "assign: \\="; //Very Important as '=' is a reserved symbol.

    int type = RulesConverter::CheckType(str);

    ASSERT_EQ(type,RulesConverter::REGULAR_EXPRESSION);
}

TEST(CheckType, RecognizesUnstructuredLines){
    std::string str = "jre [1]";

    int type = RulesConverter::CheckType(str);

    ASSERT_EQ(type,-1);
}

TEST(CheckType, RecognizesUnstructuredLines2){
    std::string str = "[, ; r";

    int type = RulesConverter::CheckType(str);

    ASSERT_EQ(type,-1);
}