//
// Created by Meniem on 28-Nov-23.
//

#include "gtest/gtest.h"
#include "../Util/util.h"

TEST(Split, WorksAsExpected){
    std::string str = "This is a test string.";

    std::vector<std::string> words = split(str, ' ');

    std::vector<std::string> result = {"This", "is", "a", "test", "string."};

    ASSERT_EQ(words,result);
}

TEST(Split, HandlesEmptyString){
    std::string str = "";

    std::vector<std::string> words = split(str, ' ');

    std::vector<std::string> result = {};

    ASSERT_EQ(words,result);
}