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

TEST(trimBlanksFromEnds, WorksAsExpected){
    std::string str = " \t  wow this really works    \n";

    trimBlanksFromEnds(str);

    std::string result = "wow this really works";

    ASSERT_EQ(str, result);
}

TEST(removeConsecutiveSpaces, WorksAsExpected){
    std::string str = "wow    so    many   consecutive         spaces";

    removeConsecutiveSpaces(str);

    std::string result = "wow so many consecutive spaces";

    ASSERT_EQ(str, result);
}

TEST(removeSpaces, WorksAsExpected){
    std::string str = "Spaces should be removed   ";

    removeSpaces(str);

    std::string result = "Spacesshouldberemoved";

    ASSERT_EQ(str, result);
}

TEST(removeSpaces, HandlesEmptyString){
    std::string str;

    removeSpaces(str);

    std::string result;

    ASSERT_EQ(str, result);
}