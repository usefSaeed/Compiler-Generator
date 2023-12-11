//
// Created by deffo on 03/12/23.
//

#include <unordered_map>
#include "gtest/gtest.h"
#include "../NFAConverter/NFA.h"
#include "../RulesParser/RegularDefinition.h"

TEST(IntegrationTest, FromParsingRegExpToNFA){
    RegularDefinition regularDefinition("test", "dig | let|bet");
    std::vector<RegularDefinition> regularDefinitions;
    int status = regularDefinition.standardizeRegex(regularDefinitions);

    NFA nfa = NFA();
    std::pair<State*, State*> nfaPair = nfa.convertToNfa(regularDefinition.getRegex(), "Disjunction", 0);

    // DFS traversing
    int numOfStates = 0;
    int degree = 0;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(nfaPair.first);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.find(currentState) != visited.end()){
            continue;
        }
        visited[currentState] = 1;
        int localDegree = 0;
        for(Transition transition: currentState->transitions){
            localDegree++;
            frontier.push(transition.getNextState());
        }
        if (localDegree > degree){
            degree = localDegree;
        }
        numOfStates++;
    }
    ASSERT_EQ(degree, 2);
    ASSERT_EQ(numOfStates, 22);
    ASSERT_EQ(nfaPair.second->tokenName, "Disjunction");
    ASSERT_FALSE(nfaPair.first->transitions.size() > 2);
    ASSERT_EQ(nfaPair.first->transitions.size(), 2);
    ASSERT_EQ(status, 0);
}