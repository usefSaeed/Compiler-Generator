//
// Created by usef on 12/2/2023.
//

#include "DFA.h"

DFA::DFA(NFA &nfa) : nfa(std::move(nfa)) {}

State *DFA::getStartState() {
    return startState;
}

DFA::DFA(State *startState) : startState(std::move(startState)){}
