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

TEST(parseProductions, HandlesEscapedConjunction){
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

TEST(parseProductions, HandlesEpsilon){
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

TEST(parseProductions, HandlesUsingNonTerminalWithoutDeclaration){
    std::string productions = "STATEMENT_LIST";
    GrammarConverter grammarConverter = GrammarConverter();

    int status = grammarConverter.parseProductions("METHOD_BODY", productions);


    ASSERT_EQ(status,-1);


}

TEST(parseProductions, WorksAsExpected){
    std::string productions = "DECLARATION 'int'\n"
                              "| IF\n"
                              "| WHILE\n";
    GrammarConverter grammarConverter = GrammarConverter();
    grammarConverter.validateGrammar("DECLARATION ::= 'declaration'");
    grammarConverter.validateGrammar("IF ::= 'if'");
    grammarConverter.validateGrammar("WHILE ::= 'while'");

    int status = grammarConverter.findTerminals(productions);
    int status2 = grammarConverter.parseProductions("STATEMENT", productions);

    std::vector<std::vector<std::string>> result = {{"DECLARATION", "int"}, {"IF"}, {"WHILE"}};

    ASSERT_EQ(status,0);
    ASSERT_EQ(status2,0);

    ASSERT_EQ(grammarConverter.getNonTerminals()[0].getProductions(), result);

}


