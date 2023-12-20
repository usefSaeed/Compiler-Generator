//
// Created by Meniem on 28-Nov-23.
//

#include "gtest/gtest.h"
#include "../Util/Util.h"

TEST(Split, WorksAsExpected){
    std::string str = "This is a test string.";

    std::vector<std::string> words = split(str, ' ');

    std::vector<std::string> result = {"This", "is", "a", "test", "string."};

    ASSERT_EQ(words,result);
}

TEST(Split, HandlesEmptyString){
    std::string str;

    std::vector<std::string> words = split(str, ' ');

    std::vector<std::string> result = {};

    ASSERT_EQ(words,result);
}

TEST(Split, HandlesStringWithoutDelimiter){
    std::string str = "RAY BAN";

    std::vector<std::string> words = split(str, 'c');

    std::vector<std::string> result = {"RAY BAN"};

    ASSERT_EQ(words,result);
}

TEST(SplitWithStringDelimiter, WorksAsExpected){
    std::string str = "This=>is=>a=>test=>string.";

    std::vector<std::string> words = splitWithStringDelimiter(str, "=>");

    std::vector<std::string> result = {"This", "is", "a", "test", "string."};

    ASSERT_EQ(words,result);
}

TEST(SplitWithStringDelimiter, HandlesEmptyString){
    std::string str;

    std::vector<std::string> words = splitWithStringDelimiter(str, "=>");

    std::vector<std::string> result = {};

    ASSERT_EQ(words,result);
}

TEST(SplitWithStringDelimiter, HandlesStringWithoutDelimiter){
    std::string str = "RAY BAN";

    std::vector<std::string> words = splitWithStringDelimiter(str, "=>");

    std::vector<std::string> result = {"RAY BAN"};

    ASSERT_EQ(words,result);
}

TEST(SplitWithStringDelimiter, HandlesStringWithOneSideOnly){
    std::string str = "RAY=>";

    std::vector<std::string> words = splitWithStringDelimiter(str, "=>");

    std::vector<std::string> result = {"RAY", ""};

    ASSERT_EQ(words,result);
}

TEST(TrimBlanksFromEnds, WorksAsExpected){
    std::string str = " \t  wow this really works    \n\n";

    trimBlanksFromEnds(str);

    std::string result = "wow this really works";

    ASSERT_EQ(str, result);
}

TEST(TrimBlanksFromEnds, HandlesBlanksOnly){
    std::string str = " \t  \t \n    \n\n";

    trimBlanksFromEnds(str);

    std::string result = "";

    ASSERT_EQ(str, result);
}

TEST(RemoveConsecutiveSpaces, WorksAsExpected){
    std::string str = "wow    so    many   consecutive         spaces";

    removeConsecutiveSpaces(str);

    std::string result = "wow so many consecutive spaces";

    ASSERT_EQ(str, result);
}

TEST(RemoveSpaces, WorksAsExpected){
    std::string str = "Spaces should be removed   ";

    removeSpaces(str);

    std::string result = "Spacesshouldberemoved";

    ASSERT_EQ(str, result);
}

TEST(RemoveSpaces, HandlesEmptyString){
    std::string str;

    removeSpaces(str);

    std::string result;

    ASSERT_EQ(str, result);
}

TEST(RemoveFirstAndLastChars, WorksAsExpected){
    std::string str = "[woaah woaah]";

    removeFirstAndLastChars(str);

    std::string result = "woaah woaah";

    ASSERT_EQ(str, result);
}

TEST(RemoveFirstAndLastChars, HandlesEmptyString){
    std::string str;

    removeFirstAndLastChars(str);

    std::string result;

    ASSERT_EQ(str, result);
}

TEST(JoinStrings, WorksAsExpected){
    std::vector<std::string> words = {"if", "else", "while"};

    std::string str = joinStrings(words, '|');

    std::string result = "if|else|while";

    ASSERT_EQ(str, result);
}

TEST(JoinStrings, HandlesEmptyVector){
    std::vector<std::string> words = {};

    std::string str = joinStrings(words, '|');

    std::string result;

    ASSERT_EQ(str, result);
}

TEST(JoinStrings, HandlesOneString){
    std::vector<std::string> words = {"if"};

    std::string str = joinStrings(words, '|');

    std::string result = "if";

    ASSERT_EQ(str, result);
}

TEST(SplitIntoTwo, WorksAsExpected){
    std::string str = "digit=0-9";

    std::pair<std::string, std::string> words = splitIntoTwo(str, '=');

    std::pair<std::string, std::string> result = std::make_pair("digit", "0-9");

    ASSERT_EQ(words, result);
}

TEST(SplitIntoTwo, HandlesDoubleDelimiter){
    std::string str = "digit=0-9\\=35";

    std::pair<std::string, std::string> words = splitIntoTwo(str, '=');

    std::pair<std::string, std::string> result = std::make_pair("digit", "0-9\\=35");

    ASSERT_EQ(words, result);
}

TEST(SplitIntoTwo, HandlesNoDelimiter){
    std::string str = "digit0-9";

    std::pair<std::string, std::string> words = splitIntoTwo(str, '=');

    std::pair<std::string, std::string> result = std::make_pair("digit0-9", "");

    ASSERT_EQ(words, result);
}

TEST(SplitIntoTwo, HandlesEmptyString){
    std::string str;

    std::pair<std::string, std::string> words = splitIntoTwo(str, '=');

    std::pair<std::string, std::string> result = std::make_pair("", "");

    ASSERT_EQ(words, result);
}

TEST(ReplaceAll, WorksAsExpected){
    std::string str = "'id' | 'num' | \\| EXPR \\|";

    replaceAll(str, "\\|", "\\$");

    std::string result = "'id' | 'num' | \\$ EXPR \\$";

    ASSERT_EQ(str, result);
}