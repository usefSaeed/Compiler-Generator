#include <gtest/gtest.h>
#include "../SyntaxPhase/Common/NonTerminal.h"
#include "../SyntaxPhase/GrammarParser/GrammarConverter.h"
#include "../SyntaxPhase/GrammarParser/Grammar.h"
#include "../SyntaxPhase/PredictiveParser/Token.h"
#include "../SyntaxPhase/PredictiveParser/Parser.h"

std::string g1Path = "../../GrammarTest.txt";

std::pair<Symbol*, std::unordered_map<std::pair<NonTerminal*,std::string>, ParsingTableEntry, PairHash, PairEqual>> MathExprGrammar() {
    // Lecture-Parsing-2 Example-2 p-26
    NonTerminal* E = new NonTerminal("E");
    NonTerminal* E_ = new NonTerminal("E'");
    NonTerminal* T = new NonTerminal("T");
    NonTerminal* T_ = new NonTerminal("T'");
    NonTerminal* F = new NonTerminal("F");
    Terminal* id = new Terminal("id");
    Terminal* plus = new Terminal("+");
    Terminal* mult = new Terminal("*");
    Terminal* openB = new Terminal("(");
    Terminal* closeB = new Terminal(")");
    
    std::vector<Symbol*> Eprod = {T,E_};
    std::vector<Symbol*> E_prod = {plus,T,E_};
    std::vector<Symbol*> Tprod = {F,T_};
    std::vector<Symbol*> T_prod = {mult,F,T_};
    std::vector<Symbol*> Fprod1 = {openB,E,closeB};
    std::vector<Symbol*> Fprod2 = {id};
    
    std::unordered_map<std::pair<NonTerminal*,std::string>, ParsingTableEntry, PairHash, PairEqual> parsingTable;
    parsingTable[{E,id->getName()}] = ParsingTableEntry(Eprod);
    parsingTable[{T,id->getName()}] = ParsingTableEntry(Tprod);
    parsingTable[{F,id->getName()}] = ParsingTableEntry(Fprod2);
    parsingTable[{E_,plus->getName()}] = ParsingTableEntry(E_prod);
    parsingTable[{T_,plus->getName()}] = ParsingTableEntry("epsilon");
    parsingTable[{T_,mult->getName()}] = ParsingTableEntry(T_prod);
    parsingTable[{E,openB->getName()}] = ParsingTableEntry(Eprod);
    parsingTable[{T,openB->getName()}] = ParsingTableEntry(Tprod);
    parsingTable[{F,openB->getName()}] = ParsingTableEntry(Fprod1);
    parsingTable[{E_,closeB->getName()}] = ParsingTableEntry("epsilon");
    parsingTable[{T_,closeB->getName()}] = ParsingTableEntry("epsilon");
    parsingTable[{E_,"$"}] = ParsingTableEntry("epsilon");
    parsingTable[{T_,"$"}] = ParsingTableEntry("epsilon");
    
    return {E, parsingTable};
}

TEST(ParserManualTest, ValidInput) {
    std::vector<Token> input = {
        Token("a", "a"),
        Token("b", "b"),
        Token("b", "b"),
        Token("a", "a"),
    };

    // S -> aBa 
    // B -> bB | eps
    NonTerminal *S = new NonTerminal("S");
    NonTerminal *B = new NonTerminal("B");
    Terminal *a = new Terminal("a");
    Terminal *b = new Terminal("b");

    std::vector<Symbol *> S_production_1 = {a, B, a};
    std::vector<Symbol *> B_production_1 = {b, B};

    std::unordered_map<std::pair<NonTerminal *, std::string>, ParsingTableEntry, PairHash, PairEqual> parsingTable;
    parsingTable[{S, a->getName()}] = ParsingTableEntry({a, B, a});
    parsingTable[{B, a->getName()}] = ParsingTableEntry("epsilon");
    parsingTable[{B, b->getName()}] = ParsingTableEntry({b, B});

    Parser parser(S, parsingTable);
    ParsingResult result = parser.parse(input);
    result.tree.print();
    result.printTrace();
    result.printStackTrace();
}

TEST(ParserManualTest, ValidInput2) {    
    std::vector<Token> input = {
        Token("id","x"),
        Token("+",""),
        Token("id","y"),
    };
    
    auto g = MathExprGrammar();
    auto startSymbol = g.first;
    auto parsingTable = g.second;
    
    Parser parser(startSymbol, parsingTable);
    ParsingResult result = parser.parse(input);
    result.tree.print();
    result.printTrace();
}

TEST(ParserManualTest, InvalidInputExcessToken) {    
    std::vector<Token> input = {
        Token("(","("),
        Token("id","x"),
        Token("+",""),
        Token("id","y"),
        Token(")",")"),
        Token("*","*"),
        Token("id","z"),
        Token("id","w"),
        Token("id","w"),
    };
    
    auto g = MathExprGrammar();
    auto startSymbol = g.first;
    auto parsingTable = g.second;
    
    Parser parser(startSymbol, parsingTable);
    ParsingResult result = parser.parse(input);
    result.tree.print();
    result.printTrace();
}

TEST(ParserManualTest, InvalidInputMissingToken) {    
    // P-46 left example
    NonTerminal* S = new NonTerminal("S");
    NonTerminal* A = new NonTerminal("A");
    Terminal* a = new Terminal("a");
    Terminal* b = new Terminal("b");
    Terminal* c = new Terminal("c");
    Terminal* d = new Terminal("d");
    Terminal* e = new Terminal("e");
    
    std::vector<Symbol*> S_production_1 = {A,b,S};
    std::vector<Symbol*> S_production_2 = {e};
    std::vector<Symbol*> A_production_1 = {a};
    std::vector<Symbol*> A_production_2 = {c,A,d};
    
    std::unordered_map<std::pair<NonTerminal*,std::string>, ParsingTableEntry, PairHash, PairEqual> parsingTable;
    parsingTable[{S,a->getName()}] = ParsingTableEntry(S_production_1);
    parsingTable[{A,a->getName()}] = ParsingTableEntry(A_production_1);
    parsingTable[{A,b->getName()}] = ParsingTableEntry("sync");
    parsingTable[{S,c->getName()}] = ParsingTableEntry(S_production_1);
    parsingTable[{A,c->getName()}] = ParsingTableEntry(A_production_2);
    parsingTable[{A,d->getName()}] = ParsingTableEntry("sync");
    parsingTable[{S,e->getName()}] = ParsingTableEntry(S_production_2);
    parsingTable[{S,"$"}] = ParsingTableEntry("epsilon");
    
    
    std::vector<Token> input = {
        Token("a","a"),
        Token("a","a"),
        Token("b","b")
    };
    
    Parser parser(S, parsingTable);
    ParsingResult result = parser.parse(input);
    result.tree.print();
    result.printTrace();
}

TEST(ParserManualTest, InvalidInputExcessToken2) {    
    // P-46 left example
    NonTerminal* S = new NonTerminal("S");
    NonTerminal* A = new NonTerminal("A");
    Terminal* a = new Terminal("a");
    Terminal* b = new Terminal("b");
    Terminal* c = new Terminal("c");
    Terminal* d = new Terminal("d");
    Terminal* e = new Terminal("e");
    
    std::vector<Symbol*> S_production_1 = {A,b,S};
    std::vector<Symbol*> S_production_2 = {e};
    std::vector<Symbol*> A_production_1 = {a};
    std::vector<Symbol*> A_production_2 = {c,A,d};
    
    std::unordered_map<std::pair<NonTerminal*,std::string>, ParsingTableEntry, PairHash, PairEqual> parsingTable;
    parsingTable[{S,a->getName()}] = ParsingTableEntry(S_production_1);
    parsingTable[{A,a->getName()}] = ParsingTableEntry(A_production_1);
    parsingTable[{A,b->getName()}] = ParsingTableEntry("sync");
    parsingTable[{S,c->getName()}] = ParsingTableEntry(S_production_1);
    parsingTable[{A,c->getName()}] = ParsingTableEntry(A_production_2);
    parsingTable[{A,d->getName()}] = ParsingTableEntry("sync");
    parsingTable[{S,e->getName()}] = ParsingTableEntry(S_production_2);
    parsingTable[{S,"$"}] = ParsingTableEntry("epsilon");
    
    
    std::vector<Token> input = {
        Token("c","c"),
        Token("e","e"),
        Token("a","a"),
        Token("d","d"),
        Token("b","b"),
    };
    
    Parser parser(S, parsingTable);
    ParsingResult result = parser.parse(input);
    result.tree.print();
    result.printTrace();   
}

TEST(ParserManualTest, InvalidInputEmptyWhileStackNot) {
    std::vector<Token> input = {
            Token("id", "x"),
            Token("+", ""),
            // Token("id","y"),
    };

    auto g = MathExprGrammar();
    auto startSymbol = g.first;
    auto parsingTable = g.second;

    Parser parser(startSymbol, parsingTable);
    ParsingResult result = parser.parse(input);
    result.tree.print();
    result.printTrace();
}
