//
// Created by Zyad Samy on 08/12/2023.
//

#include "gtest/gtest.h"
#include "../LexicalPhase/DFAConverter//DFA.h"

TEST(NFAToDFAConversion, TestCase1) {
    State* q0 = new State("N1");
    q0->priority = 2;
    State* q1 = new State();

    q0->addTransition(Transition('b', q0));
    q0->addTransition(Transition('a', q1));
    q0->addTransition(Transition(EPSILON, q1));

    q1->addTransition(Transition('b', q0));

    DFA dfa(q0);
    State* s0 = dfa.getStartState();

    State* s1 = s0->moveTo('a');
    State* s2 = s0->moveTo('b');

    ASSERT_EQ(s0->isFinal, true);
    ASSERT_EQ(s1->isFinal, false);
    ASSERT_EQ(s2->isFinal, true);

    ASSERT_EQ(s2->moveTo('a'), s1);
    ASSERT_EQ(s1->moveTo('b'), s2);

    ASSERT_EQ(s0->tokenName, "N1");
    ASSERT_EQ(s1->tokenName, "");

    int numOfStates = 0;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(s0);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.find(currentState) != visited.end()){
            continue;
        }
        visited[currentState] = 1;
        for(Transition transition: currentState->transitions){
            frontier.push(transition.getNextState());
        }
        numOfStates++;
    }

    ASSERT_EQ(numOfStates, 2);
}

TEST(NFAToDFAConversion, TestCase2) {
    State* q0 = new State();
    State* q1 = new State();
    State* q2 = new State("final");

    q0->addTransition(Transition('0', q0));
    q0->addTransition(Transition('0', q1));
    q0->addTransition(Transition('1', q0));

    q1->addTransition(Transition('1', q2));

    q2->addTransition(Transition('0', q2));
    q2->addTransition(Transition('1', q2));

    DFA dfa(q0);
    State* s0 = dfa.getStartState();
    State* s1 = s0->moveTo('0');
    State* s2 = s1->moveTo('1');
    State* s3 = s2->moveTo('0');

    ASSERT_EQ(s0->isFinal, false);
    ASSERT_EQ(s1->isFinal, false);
    ASSERT_EQ(s2->isFinal, true);
    ASSERT_EQ(s3->isFinal, true);

    ASSERT_EQ(s0->moveTo('1'), s0);
    ASSERT_EQ(s1->moveTo('0'), s1);
    ASSERT_EQ(s2->moveTo('1'), s2);
    ASSERT_EQ(s3->moveTo('0'), s3);
    ASSERT_EQ(s3->moveTo('1'), s2);

    std::vector<State*> states;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(s0);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.find(currentState) != visited.end()){
            continue;
        }
        visited[currentState] = 1;
        for(Transition transition: currentState->transitions){
            frontier.push(transition.getNextState());
        }
        states.push_back(currentState);
    }

    ASSERT_EQ(states.size(), 4);
}

TEST(MinimizeDFA, MTestCase1) {
    State* A = new State();
    State* B = new State();
    State* C = new State();
    State* D = new State();
    State* E = new State("E");

    A->addTransition(Transition('a', B));
    A->addTransition(Transition('b', C));

    B->addTransition(Transition('a', B));
    B->addTransition(Transition('b', D));

    C->addTransition(Transition('a', B));
    C->addTransition(Transition('b', C));

    D->addTransition(Transition('a', B));
    D->addTransition(Transition('b', E));

    E->addTransition(Transition('a', B));
    E->addTransition(Transition('b', C));


    DFA dfa(A);
    State* s0 = dfa.getStartState();

    State* m0 = dfa.minimize();

    int numOfStates = 0;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(m0);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.find(currentState) != visited.end()){
            continue;
        }
        visited[currentState] = 1;
        for(Transition transition: currentState->transitions){
            frontier.push(transition.getNextState());
        }
        numOfStates++;
    }

    ASSERT_EQ(numOfStates, 4);
}

TEST(MinimizeDFA, MTestCase2) {
    State* q1 = new State("Final");
    State* q2 = new State();
    State* q3 = new State();
    State* q4 = new State();
    State* q5 = new State("Final");

    q1->addTransition(Transition('a', q3));
    q1->addTransition(Transition('b', q2));

    q2->addTransition(Transition('a', q4));
    q2->addTransition(Transition('b', q1));

    q3->addTransition(Transition('a', q5));
    q3->addTransition(Transition('b', q4));

    q4->addTransition(Transition('a', q4));
    q4->addTransition(Transition('b', q4));

    q5->addTransition(Transition('a', q3));
    q5->addTransition(Transition('b', q2));

    DFA dfa(q1);

    State* m0 = dfa.minimize();

    int numOfStates = 0;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(m0);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.find(currentState) != visited.end()){
            continue;
        }
        visited[currentState] = 1;
        for(Transition transition: currentState->transitions){
            frontier.push(transition.getNextState());
        }
        numOfStates++;
    }

    ASSERT_EQ(numOfStates, 4);
}

TEST(MinimizeDFA, MTestCase3) {
    State* q0 = new State();
    State* q1 = new State();
    State* q2 = new State();
    State* q3 = new State("final");
    State* q4 = new State("final");

    q0->addTransition(Transition('0', q1));
    q0->addTransition(Transition('1', q2));

    q1->addTransition(Transition('0', q2));
    q1->addTransition(Transition('1', q3));

    q2->addTransition(Transition('0', q2));
    q2->addTransition(Transition('1', q4));

    q3->addTransition(Transition('0', q3));
    q3->addTransition(Transition('1', q3));

    q4->addTransition(Transition('0', q4));
    q4->addTransition(Transition('1', q4));


    DFA dfa(q0);

    State* m0 = dfa.minimize();

    int numOfStates = 0;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(m0);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.find(currentState) != visited.end()){
            continue;
        }
        visited[currentState] = 1;
        for(Transition transition: currentState->transitions){
            frontier.push(transition.getNextState());
        }
        numOfStates++;
    }

    ASSERT_EQ(numOfStates, 3);
}