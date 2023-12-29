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
=======
//    std::vector<NonTerminal> standardizedGrammar = grammar.getStandardizedNonTerminals();
//    NonTerminal declaration = standardizedGrammar[3];
//    std::shared_ptr<Symbol> statementList = declaration.getProductions()[0][0];
//    auto statementListCast = dynamic_pointer_cast<NonTerminal>(statementList);
//    if (statementListCast){
//        auto productions = statementListCast->getProductions();
//    }
//    else{
//        std::cout << "Terminal";
//    }


//    RulesConverter rulesConverter(argv[1]);
//    int statusCode = rulesConverter.parseFile();
//    if (statusCode == -1){
//        std::cerr << "Badly Formatted Rules File" << "\n";
//        return -1;
//    }
//
//    std::vector<RegularExpression> regularExpressions = rulesConverter.getRegularExpressions();
//
//    for (const RegularExpression& regExp : regularExpressions) {
//        std::cout << regExp.toString() << "\n";
//    }
//
//    // Regular expressions conversion to NFA
//    NFACombiner nfaCombiner(regularExpressions);
//    std::unordered_map<std::pair<State*, char>, std::vector<State*>, PairHash, PairEqual> table = nfaCombiner.extractTableRepresentation();
//    State* nfaComplete = nfaCombiner.getCompleteNfa();
//
//    std::cout << "degree of the start state in NFA: " << nfaComplete->transitions.size() << '\n';
//
//    DFA dfa(nfaComplete);
//    State* dfaStartState = dfa.getStartState();
//
//    int states = 0;
//    std::stack<State*> frontier;
//    std::unordered_map<State*, int> visited;
//    frontier.push(dfaStartState);
//    while(not frontier.empty()){
//        State* currentState = frontier.top();
//        frontier.pop();
//        if(visited.find(currentState) != visited.end()){
//            continue;
//        }
//        states += 1;
//        visited[currentState] = 1;
//        for(Transition transition: currentState->transitions){
//            frontier.push(transition.getNextState());
//            std::cout << currentState << " with input: " << transition.getInput() << " ,to state: " << transition.getNextState() << '\n';
//        }
//    }
//    std::cout << "num of DFA states: " << states << '\n';
//
//    State* minimzedDFAStartState = dfa.minimize();
//
//    int minimizedStates = 0;
//    std::stack<State*> minimizedFrontier;
//    std::unordered_map<State*, int> minimizedVisited;
//    minimizedFrontier.push(minimzedDFAStartState);
//    while(not minimizedFrontier.empty()){
//        State* miniCurrentState = minimizedFrontier.top();
//        minimizedFrontier.pop();
//        if(minimizedVisited.find(miniCurrentState) != minimizedVisited.end()){
//            continue;
//        }
//        minimizedStates += 1;
//        minimizedVisited[miniCurrentState] = 1;
//        for(Transition transition: miniCurrentState->transitions){
//            minimizedFrontier.push(transition.getNextState());
//            std::cout << miniCurrentState << " with input: " << transition.getInput() << " ,to state: " << transition.getNextState() << '\n';
//        }
//    }
//    std::cout << "num of minimized DFA states: " << minimizedStates << '\n';
//
//    STGenerator stg(dfa);
//    std::cout << "Run all files in dir --> a\nRun specific file --> s\n> ";
//    std::string input;
//    std::getline(std::cin, input);
//    std::string dirPath;
//    if (input == "a") {
//        std::cout << "Enter the directory path: ";
//        std::getline(std::cin, dirPath);
//        for (const auto &entry: std::filesystem::directory_iterator(dirPath)) {
//            if (entry.is_regular_file()) {
//                std::string scriptFilePath = entry.path().string();
//                std::cout << "Running: " << scriptFilePath << std::endl;
//                stg.execute(scriptFilePath);
//                std::cout << "\n#############W####" << std::endl;
//            }
//        }
//    } else if (input == "s") {
//        while (true) {
//            std::cout << "Enter the file path: ";
//            std::string scriptFilePath;
//            std::getline(std::cin, scriptFilePath);
//            if (scriptFilePath == "$")
//                break;
//            stg.execute(scriptFilePath);
//            std::cout << "\n#############W####" << std::endl;
//        }
//    }else{
//        std::cout << "Invalid input. Program Terminated." << std::endl;
//    }

>>>>>>> .merge_file_D0zfMT

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