#include <iostream>
#include <unordered_map>
#include "RulesParser/RulesConverter.h"
#include "NFAConverter/NFACombiner.h"
#include "DFAConverter/DFA.h"
#include "SymbolTableGenerator/STGenerator.h"

int main(int argc, char *argv[]) {

    if (argc != 2){
        std::cerr << "Wrong number of parameter (One argument required: Rules File Path)" << "\n";
        return -1;
    }

    RulesConverter rulesConverter(argv[1]);
    int statusCode = rulesConverter.parseFile();
    if (statusCode == -1){
        std::cerr << "Badly Formatted Rules File" << "\n";
        return -1;
    }

    std::vector<RegularExpression> regularExpressions = rulesConverter.getRegularExpressions();

    for (const RegularExpression& regExp : regularExpressions) {
        std::cout << regExp.toString() << "\n";
    }

    // Regular expressions conversion to NFA
    NFACombiner nfaCombiner(regularExpressions);
    std::unordered_map<std::pair<State*, char>, std::vector<State*>, PairHash, PairEqual> table = nfaCombiner.extractTableRepresentation();
    State* nfaComplete = nfaCombiner.getCompleteNfa();

    std::cout << "degree of the start state in NFA: " << nfaComplete->transitions.size() << '\n';

    DFA dfa(nfaComplete);
    State* dfaStartState = dfa.getStartState();

    int states = 0;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(dfaStartState);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.find(currentState) != visited.end()){
            continue;
        }
        states += 1;
        visited[currentState] = 1;
        for(Transition transition: currentState->transitions){
            frontier.push(transition.getNextState());
            std::cout << currentState << " with input: " << transition.getInput() << " ,to state: " << transition.getNextState() << '\n';
        }
    }
    std::cout << "num of DFA states: " << states << '\n';

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

    STGenerator stg(dfa);
    while (true){
        std::cout << "Enter the file path: ";
        std::string scriptFilePath;
        std::getline(std::cin, scriptFilePath);
        if (scriptFilePath=="$")
            break;
        stg.execute(scriptFilePath);
    }
    return 0;
}