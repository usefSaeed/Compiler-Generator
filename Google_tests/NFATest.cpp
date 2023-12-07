//
// Created by deffo on 03/12/23.
//
#include "gtest/gtest.h"
#include "../NFAConverter/NFA.h"

TEST(RegexToNfaConversion, SimpleConcatenation){
    NFA nfa = NFA();
    std::pair<State*, State*> nfaPair = nfa.convertToNfa("boolean", "boolean", 0);

    // DFS traversing
    int numOfStates = 0;
    int degree = 0;
    std::stack<State*> frontier;
    frontier.push(nfaPair.first);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
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
    ASSERT_EQ(degree, 1);
    ASSERT_EQ(numOfStates, 14);
    ASSERT_EQ(nfaPair.second->tokenName, "boolean");
    ASSERT_FALSE(nfaPair.first->transitions.size() > 1);
}
TEST(RegexToNfaConversion, SimpleKleeneClosure){
    NFA nfa = NFA();
    std::pair<State*, State*> nfaPair = nfa.convertToNfa("(boolean)*", "repeated boolean", 0);

    // DFS traversing
    int numOfStates = 0;
    int degree = 0;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(nfaPair.first);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.contains(currentState)){
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
    ASSERT_EQ(numOfStates, 16);
    ASSERT_EQ(nfaPair.second->tokenName, "repeated boolean");
    ASSERT_FALSE(nfaPair.first->transitions.size() > 2);
}
TEST(RegexToNfaConversion, SimplePositiveClosure){
    NFA nfa = NFA();
    std::pair<State*, State*> nfaPair = nfa.convertToNfa("(boolean)+", "repeated boolean", 0);

    // DFS traversing
    int numOfStates = 0;
    int degree = 0;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(nfaPair.first);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.contains(currentState)){
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
    ASSERT_EQ(numOfStates, 16);
    ASSERT_EQ(nfaPair.second->tokenName, "repeated boolean");
    ASSERT_FALSE(nfaPair.first->transitions.size() > 1);
}
TEST(RegexToNfaConversion, SimpleDisjunction){
    NFA nfa = NFA();
    std::pair<State*, State*> nfaPair = nfa.convertToNfa("(b)|(a)", "or", 0);

    // DFS traversing
    int numOfStates = 0;
    int degree = 0;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(nfaPair.first);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.contains(currentState)){
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
    ASSERT_EQ(numOfStates, 6);
    ASSERT_EQ(nfaPair.second->tokenName, "or");
    ASSERT_FALSE(nfaPair.first->transitions.size() > 2);
    ASSERT_EQ(nfaPair.first->transitions.size(), 2);
}
TEST(RegexToNfaConversion, SimpleSkipCharacters){
    NFA nfa = NFA();
    std::pair<State*, State*> nfaPair = nfa.convertToNfa("\\(a\\=\\=h\\)", "skip characters", 0);

    // DFS traversing
    int numOfStates = 0;
    int degree = 0;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(nfaPair.first);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.contains(currentState)){
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
    ASSERT_EQ(degree, 1);
    ASSERT_EQ(numOfStates, 12);
    ASSERT_EQ(nfaPair.second->tokenName, "skip characters");
    ASSERT_FALSE(nfaPair.first->transitions.size() > 1);
}
TEST(RegexToNfaConversion, DisjunctionWithConcatenation){
    NFA nfa = NFA();
    std::pair<State*, State*> nfaPair = nfa.convertToNfa("sad:((b)|(a))", "combination", 0);

    // DFS traversing
    int numOfStates = 0;
    int degree = 0;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(nfaPair.first);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.contains(currentState)){
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
    ASSERT_EQ(numOfStates, 14);
    ASSERT_EQ(nfaPair.second->tokenName, "combination");
    ASSERT_FALSE(nfaPair.first->transitions.size() > 1);
    ASSERT_EQ(nfaPair.first->transitions.size(), 1);
}
TEST(RegexToNfaConversion, DisjunctionWithKleeneClosure){
    NFA nfa = NFA();
    std::pair<State*, State*> nfaPair = nfa.convertToNfa("((b)|(a))*", "combination", 0);

    // DFS traversing
    int numOfStates = 0;
    int degree = 0;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(nfaPair.first);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.contains(currentState)){
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
    ASSERT_EQ(numOfStates, 8);
    ASSERT_EQ(nfaPair.second->tokenName, "combination");
    ASSERT_FALSE(nfaPair.first->transitions.size() > 2);
    ASSERT_EQ(nfaPair.first->transitions.size(), 2);
}
TEST(RegexToNfaConversion, DisjunctionContainsEpsilonWithKleeneClosure){
    NFA nfa = NFA();
    std::pair<State*, State*> nfaPair = nfa.convertToNfa("((\\L)|(a))*", "combination", 0);

    // DFS traversing
    int numOfStates = 0;
    int degree = 0;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(nfaPair.first);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.contains(currentState)){
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
    ASSERT_EQ(numOfStates, 8);
    ASSERT_EQ(nfaPair.second->tokenName, "combination");
    ASSERT_FALSE(nfaPair.first->transitions.size() > 2);
    ASSERT_EQ(nfaPair.first->transitions.size(), 2);
}