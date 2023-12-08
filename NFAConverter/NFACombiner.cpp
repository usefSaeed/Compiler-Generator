//
// Created by deffo on 02/12/23.
//

#include "NFACombiner.h"

NFACombiner::NFACombiner(std::vector<RegularExpression>& regExps) {
    State* initial = new State();
    for (const RegularExpression& regExp: regExps){
        NFA nfa = NFA();
        std::pair<State*, State*> localNfa = nfa.convertToNfa(regExp.getRegex(), regExp.getName(), regExp.getPriority());
        NFA::addEpsilonTransition(initial, localNfa.first);
    }
    this->completeNfa = initial;
}

std::unordered_map<std::pair<State*, char>, std::vector<State*>, PairHash, PairEqual> NFACombiner::extractTableRepresentation() {
    std::unordered_map<std::pair<State*, char>, std::vector<State*>, PairHash, PairEqual> table;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(completeNfa);
    while (not frontier.empty()) {
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.find(currentState) != visited.end()){
            continue;
        }
        visited[currentState] = 1;
        for (Transition transition: currentState->transitions) {
            table[std::pair(currentState, transition.getInput())].push_back(transition.getNextState());
            frontier.push(transition.getNextState());
        }
    }
    return table;
}

State* NFACombiner::getCompleteNfa() {
    return completeNfa;
}
