#include <iostream>
#include <unordered_map>
#include <filesystem>
#include "LexicalPhase/RulesParser/RulesConverter.h"
#include "LexicalPhase/NFAConverter/NFACombiner.h"
#include "LexicalPhase/DFAConverter/DFA.h"
#include "LexicalPhase/SymbolTableGenerator/STGenerator.h"
#include "SyntaxPhase/GrammarParser/GrammarConverter.h"
#include "SyntaxPhase/GrammarParser/Grammar.h"
#include "SyntaxPhase/FirstAndFollowGenerator/FirstSetsGenerator.h"
#include "SyntaxPhase/FirstAndFollowGenerator/FollowSetsGenerator.h"
#include "SyntaxPhase/PredictiveParser/Parser.h"

#include "unordered_set"
#include "string"

std::vector<Token> getTokens(LAOutput output);

int main(int argc, char *argv[]) {
    int statusCode;
    
    if (argc != 3)
    {
        std::cerr << "Wrong number of parameter (2 arguments required: Rules File Path, Grammar File Path)"
                  << "\n";
        return -1;
    }
    
    auto rulesFilePath = argv[1];
    auto grammarFilePath = argv[2];
    
    // Parse rules file
    RulesConverter rulesConverter(rulesFilePath);
    statusCode = rulesConverter.parseFile();
    if (statusCode == -1){
        std::cerr << "Badly Formatted Rules File" << "\n";
        return -1;
    }

    // Rules to Regular Expressions
    std::vector<RegularExpression> regularExpressions = rulesConverter.getRegularExpressions();
    for (const RegularExpression& regExp : regularExpressions) {
        std::cout << regExp.toString() << "\n";
    }

    // Regular expressions conversion to NFA
    NFACombiner nfaCombiner(regularExpressions);
    auto table = nfaCombiner.extractTableRepresentation();
    State* nfaComplete = nfaCombiner.getCompleteNfa();

    // NFA to DFA
    DFA dfa(nfaComplete);
    STGenerator stg(dfa);
    
    // parse Grammar file
    GrammarConverter grammarConverter;
    statusCode = grammarConverter.parseFile(grammarFilePath);
    if (statusCode == -1)
        return -1;

    bool leftFactored = grammarConverter.leftFactor();
    if (leftFactored){
        std::cout<< "Grammar was not left factored but left factoring was eliminated successfully." << "\n";
    }

    bool leftRecursion = grammarConverter.eliminateLeftRecursion();
    if (leftRecursion){
        std::cout<< "Grammar had left recursion but was eliminated successfully." << "\n";
    }
    
    // Generate grammar
    Grammar grammar(grammarConverter);
    std::cout << grammar;
    grammar.standardizeNonTerminals();
    std::cout << "\n\n\n";

    Parser parser(grammar);
    parser.printParsingTable();
    parser.writeParsingTableToCSV();
    std::cout << "success";

    // Read input file
    while (true) {
        // Get input path
        std::cout << "\n\nEnter the file path: ";
        std::string inputFilePath;
        std::getline(std::cin, inputFilePath);  
        if (inputFilePath == "$")
            break;
            
        // Read file into tokens
        LAOutput LAout = stg.execute(inputFilePath);
        std::vector<Token> tokens = getTokens(LAout);
        std::cout << "\n\n";
        // Parse tokens
        auto result = parser.parse(tokens);
        std::cout << "<<Parsing Tree>>\n";
        result.tree.print();
        std::cout << "\n<<Parsing Stack Trace>>\n";
        result.printTrace();
    }    

    return 0;
}

std::vector<Token> getTokens(LAOutput output) {
    std::vector<Token> tokens;
    auto symbolTable = output.getSymbolTable();
    for (auto& row: symbolTable) {
        tokens.push_back(Token(row.getTokenType(), row.getToken()));
    }
    return tokens;
}