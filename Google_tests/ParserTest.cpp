#include <gtest/gtest.h>
#include "../ParserPhase/PredictiveParser/Parser.h"

#define MULTILINE(...) #__VA_ARGS__ 

// Define a fixture for the parser tests
// class ParserTest : public ::testing::Test {
// protected:
//     // Declare variables needed for the tests
//     Parser parser;
// };

// Test case for parsing valid input
TEST(ParserTest, ValidInputParsing) {
    // Define your tokens and grammar for valid input
    std::vector<Token*> tokens = {
        new Token("ident","x"),
        new Token("+","+"),
        new Token("num","5"),
        new Token("*","*"),
        new Token("ident","y"),
    };
    
    std::string grammarString = 
        "Expr -> Term + Expr | Term - Expr | Term \
        Term -> Factor * Term | Factor / Term | Factor \
        Factor -> (Expr) | Number \
        Number -> [0-9]+";
    
    
    // Grammar grammar = /* define your grammar */;

    // Parse the input
    // ParsingTree tree = parser.parse(tokens, grammar);

    // Assert that the parsing tree is constructed correctly
    // ASSERT_TRUE(/* perform assertions on the parsing tree */);
}

// // Test case for parsing invalid input
// TEST_F(ParserTest, InvalidInputParsing) {
//     // Define your tokens and grammar for invalid input
//     std::vector<Token> tokens = /* define invalid tokens */;
//     Grammar grammar = /* define your grammar */;

//     // Parse the invalid input
//     ParsingTree tree = parser.parse(tokens, grammar);

//     // Assert that the parsing tree is not constructed or is invalid
//     ASSERT_FALSE(/* perform assertions on the parsing tree */);
// }
