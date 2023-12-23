//
// Created by Meniem on 19-Dec-23.
//
#include "gtest/gtest.h"
#include "../SyntaxPhase/GrammarParser/GrammarConverter.h"

TEST(ValidateGrammar, HandlesNoSeperator){
    std::string str = "METHOD_BODY  STATEMENT_LIST";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.validateGrammar(str);

    ASSERT_EQ(status,-1);
}

TEST(ValidateGrammar, HandlesMoreThanOneSeperator){
    std::string str = "METHOD_BODY ::= ::= STATEMENT_LIST ::= ";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.validateGrammar(str);

    ASSERT_EQ(status,-1);
}

TEST(ValidateGrammar, HandlesRightSideOnlyBlanks){
    std::string str = "METHOD_BODY ::=   \n  \n \t";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.validateGrammar(str);

    ASSERT_EQ(status,-1);
}

TEST(ValidateGrammar, HandlesLeftSideOnlyBlanks){
    std::string str = " \t \n::=  STATEMENT_LIST  \n";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.validateGrammar(str);

    ASSERT_EQ(status,-1);
}

TEST(ValidateGrammar, RedundantDefinition){
    std::string str = "METHOD_BODY ::=  STATEMENT_LIST";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.validateGrammar(str);

    ASSERT_EQ(status,0);

    std::string str2 = "METHOD_BODY ::=  'int'";

    status = grammarConverter.validateGrammar(str2);

    ASSERT_EQ(status,-1);
}

TEST(FindTerminals, WorksAsExpected){
    std::string str = "LIST 'int' HDAUG 'float' \n";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.findTerminals(str);

    ASSERT_EQ(status, 0);
    ASSERT_EQ(grammarConverter.getTerminals().size(),2);
    ASSERT_TRUE(grammarConverter.getTerminals().contains("int"));
    ASSERT_TRUE(grammarConverter.getTerminals().contains("float"));

}

TEST(FindTerminals, HandlesEscapedQuote){
    std::string str = "LIST 'int\\'r' HDAUG 'float\\'' \\' RAT \n";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.findTerminals(str);

    ASSERT_EQ(status, 0);
    ASSERT_EQ(grammarConverter.getTerminals().size(),2);
    ASSERT_TRUE(grammarConverter.getTerminals().contains("int'r"));
    ASSERT_TRUE(grammarConverter.getTerminals().contains("float'"));

}

TEST(FindTerminals, HandlesNonClosedQuotes){
    std::string str = "LIST 'int' RAT 'asr NAT \n";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.findTerminals(str);
    ASSERT_EQ(status, -1);

}

TEST(ParseProductions, HandlesEscapedConjunction){
    std::string productions = "'id' | 'num' | '(' '\\|' 'float' ')'";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.findTerminals(productions);
    int status2 = grammarConverter.parseProductions("FACTOR", productions);

    std::vector<std::vector<std::string>> result = {{"id"}, {"num"}, {"(", "|", "float", ")"}};

    ASSERT_EQ(status,0);
    ASSERT_EQ(status2,0);

    ASSERT_EQ(grammarConverter.getNonTerminals().size(), 1);
    ASSERT_EQ(grammarConverter.getNonTerminals()[0].getProductions(), result);

}

TEST(ParseProductions, HandlesEpsilon){
    std::string productions = "'id' | \\L";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.findTerminals(productions);
    int status2 = grammarConverter.parseProductions("FACTOR", productions);

    std::vector<std::vector<std::string>> result = {{"id"}, {"\\L"}};

    ASSERT_EQ(status,0);
    ASSERT_EQ(status2,0);

    ASSERT_EQ(grammarConverter.getNonTerminals().size(), 1);
    ASSERT_EQ(grammarConverter.getNonTerminals()[0].getProductions(), result);

}

TEST(ParseProductions, HandlesUsingNonTerminalWithoutDeclaration){
    std::string productions = "STATEMENT_LIST";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.parseProductions("METHOD_BODY", productions);


    ASSERT_EQ(status,-1);


}

TEST(ParseProductions, WorksAsExpected){
    std::string productions = "DECLARATION 'int'\n"
                              "| IF\n"
                              "| WHILE\n";
    GrammarConverter grammarConverter = GrammarConverter();
    int status = grammarConverter.validateGrammar("DECLARATION ::= 'declaration'");
    int status1 = grammarConverter.validateGrammar("IF ::= 'if'");
    int status2 = grammarConverter.validateGrammar("WHILE ::= 'while'");

    int status3 = grammarConverter.findTerminals(productions);
    int status4 = grammarConverter.parseProductions("STATEMENT", productions);

    std::vector<std::vector<std::string>> result = {{"DECLARATION", "int"}, {"IF"}, {"WHILE"}};

    ASSERT_EQ(status,0);
    ASSERT_EQ(status1,0);
    ASSERT_EQ(status2,0);
    ASSERT_EQ(status3,0);
    ASSERT_EQ(status4,0);
    ASSERT_EQ(grammarConverter.getNonTerminals()[0].getProductions(), result);
}

TEST(LeftFactor, DetectsNoLeftFactoring){
    std::string productions = "'id' | 'float' | 'boolean'";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.findTerminals(productions);
    int status2 = grammarConverter.parseProductions("TYPES", productions);
    bool leftFactor = grammarConverter.leftFactor();

    std::vector<std::vector<std::string>> result = {{"id"}, {"float"}, {"boolean"}};

    ASSERT_EQ(status,0);
    ASSERT_EQ(status2,0);
    ASSERT_FALSE(leftFactor);
    ASSERT_EQ(grammarConverter.getNonTerminals().size(), 1);
    ASSERT_EQ(grammarConverter.getNonTerminals()[0].getProductions(), result);
}

TEST(LeftFactor, WorksAsExpected){
    std::string productions = "'a' 'd' | 'a' | 'a' 'b' | 'a' 'b' 'c' | 'b'";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.findTerminals(productions);
    int status2 = grammarConverter.parseProductions("A", productions);
    bool leftFactor = grammarConverter.leftFactor();

    std::vector<std::vector<std::string>> res0 = {{"a", "A1"}, {"b"}};
    std::vector<std::vector<std::string>> res1 = {{"\\L"}, {"b", "A11"}, {"d"}};
    std::vector<std::vector<std::string>> res2 = {{"\\L"}, {"c"}};

    ASSERT_EQ(status,0);
    ASSERT_EQ(status2,0);
    ASSERT_TRUE(leftFactor);
    ASSERT_EQ(grammarConverter.getNonTerminals().size(), 3);
    ASSERT_EQ(grammarConverter.getNonTerminals()[0].getProductions(), res0);
    ASSERT_EQ(grammarConverter.getNonTerminals()[1].getProductions(), res1);
    ASSERT_EQ(grammarConverter.getNonTerminals()[2].getProductions(), res2);

}

TEST(LeftFactor, WorksAsExpected2){
    std::string productions = "'a' 'b' B | 'a' B | 'c' 'd' 'g' | 'c' 'd' 'e' B | 'c' 'd' 'f' B ";
    GrammarConverter grammarConverter = GrammarConverter();
    int status = grammarConverter.validateGrammar("B ::= 'irrelevant'");

    int status1 = grammarConverter.findTerminals(productions);
    int status2 = grammarConverter.parseProductions("A", productions);
    bool leftFactor = grammarConverter.leftFactor();

    std::vector<std::vector<std::string>> A = {{"a", "A1"}, {"c", "A2"}};
    std::vector<std::vector<std::string>> A1 = {{"b", "B"}, {"B"}};
    std::vector<std::vector<std::string>> A2 = {{"d", "A21"}};
    std::vector<std::vector<std::string>> A21 = {{"g"}, {"e", "B"}, {"f", "B"}};

    ASSERT_EQ(status,0);
    ASSERT_EQ(status1,0);
    ASSERT_EQ(status2,0);
    ASSERT_TRUE(leftFactor);
    ASSERT_EQ(grammarConverter.getNonTerminals().size(), 4);
    ASSERT_EQ(grammarConverter.getNonTerminals()[0].getProductions(), A);
    ASSERT_EQ(grammarConverter.getNonTerminals()[1].getProductions(), A1);
    ASSERT_EQ(grammarConverter.getNonTerminals()[2].getProductions(), A2);
    ASSERT_EQ(grammarConverter.getNonTerminals()[3].getProductions(), A21);

}

TEST(EliminateLeftRecursion, DetectsNoLeftRecursion){
    std::string productions = "'id' | 'float' | BODY 'boolean'";
    GrammarConverter grammarConverter = GrammarConverter();
    int status = grammarConverter.validateGrammar("BODY ::= 'irrelevant'");

    int status1 = grammarConverter.findTerminals(productions);
    int status2 = grammarConverter.parseProductions("TYPES", productions);
    bool leftRecursion = grammarConverter.eliminateLeftRecursion();

    std::vector<std::vector<std::string>> result = {{"id"}, {"float"}, {"BODY", "boolean"}};

    ASSERT_EQ(status,0);
    ASSERT_EQ(status1,0);
    ASSERT_EQ(status2,0);
    ASSERT_FALSE(leftRecursion);
    ASSERT_EQ(grammarConverter.getNonTerminals().size(), 1);
    ASSERT_EQ(grammarConverter.getNonTerminals()[0].getProductions(), result);
}

TEST(EliminateLeftRecursion, WorksAsExpected){
    std::string productions1 = "A 'a' | 'b'";
    std::string productions2 = "A 'c' | S 'd' | 'e'";
    GrammarConverter grammarConverter = GrammarConverter();
    int status = grammarConverter.validateGrammar("S ::= 'irrelevant'");
    int status1 = grammarConverter.validateGrammar("A ::= 'irrelevant'");

    int status2 = grammarConverter.findTerminals(productions1);
    int status3 = grammarConverter.parseProductions("S", productions1);
    int status4 = grammarConverter.findTerminals(productions2);
    int status5 = grammarConverter.parseProductions("A", productions2);

    bool leftRecursion = grammarConverter.eliminateLeftRecursion();

    std::vector<std::vector<std::string>> S = {{"A", "a"}, {"b"}};
    std::vector<std::vector<std::string>> A = {{"b", "d", "A`"}, {"e", "A`"}};
    std::vector<std::vector<std::string>> A1 = {{"c", "A`"}, {"a", "d", "A`"}, {"\\L"}};

    ASSERT_EQ(status,0);
    ASSERT_EQ(status1,0);
    ASSERT_EQ(status2,0);
    ASSERT_EQ(status3,0);
    ASSERT_EQ(status4,0);
    ASSERT_EQ(status5,0);
    ASSERT_TRUE(leftRecursion);
    ASSERT_EQ(grammarConverter.getNonTerminals().size(), 3);
    ASSERT_EQ(grammarConverter.getNonTerminals()[0].getProductions(), S);
    ASSERT_EQ(grammarConverter.getNonTerminals()[1].getProductions(), A);
    ASSERT_EQ(grammarConverter.getNonTerminals()[2].getProductions(), A1);
}





