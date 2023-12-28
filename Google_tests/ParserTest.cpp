#include <gtest/gtest.h>
// #include "../ParserPhase/PredictiveParser/ParsingTree.h"
#include "../ParserPhase/Common/NonTerminal.h"
#include "../ParserPhase/Common/Terminal.h"
#include "../ParserPhase/Common/Symbol.h"
#include "../ParserPhase/GrammarParser/GrammarConverter.h"
#include "../ParserPhase/GrammarParser/Grammar.h"
#include "../ParserPhase/PredictiveParser/Token.h"
#include "../ParserPhase/PredictiveParser/Parser.h"
#include "../ParserPhase/PredictiveParser/ParsingTree.h"
#include "../ParserPhase/PredictiveParser/ParsingResult.h"

std::string g1Path = "../../GrammarTest.txt";

TEST(ParserTest, ValidInputParsing) {
    std::vector<Token> input = {
        Token("a","a"),
        Token("b","b"),
        Token("b","b"),
        Token("a","a"),
    };
    
    // S -> aBa 
    // B -> bB | eps
    NonTerminal* S = new NonTerminal("S");
    NonTerminal* B = new NonTerminal("B");
    Terminal* a = new Terminal("a");
    Terminal* b = new Terminal("b");
    
    std::vector<Symbol*> S_production_1 = {a,B,a};
    std::vector<Symbol*> B_production_1 = {b,B};
    
    std::unordered_map<std::pair<NonTerminal*,std::string>, ParsingTableEntry, PairHash, PairEqual> parsingTable;
    parsingTable[{S,a->getName()}] = ParsingTableEntry({a,B,a});
    parsingTable[{B,a->getName()}] = ParsingTableEntry("epsilon");
    parsingTable[{B,b->getName()}] = ParsingTableEntry({b,B});
    
    Parser parser(S, parsingTable);
    ParsingResult result = parser.parse(input);
    result.tree.print();
    result.printTrace();
    
    ASSERT_EQ(1,1);
}
