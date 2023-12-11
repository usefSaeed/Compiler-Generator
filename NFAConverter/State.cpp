//
// Created by deffo on 01/12/23.
//

#include "State.h"

State::State(){
    this->isFinal = false;
}
void State::addTransition(Transition transition) {
    this->transitions.push_back(transition);
}

State *State::moveTo(char input) {
    for (auto t: transitions){
        if (t.getInput()==input)
            return t.getNextState();
    }
    return nullptr;
}

State::State(const std::string& tokenName) {
    this->isFinal = true;
    this->tokenName = tokenName;
}

State::State(std::unordered_set<State*> states) {
    this->isFinal = false;
    State* highestPriorityState = *(states.begin());
    int highestPriority = 100000;

    for (State* state: states) {
        if(state->isFinal){
            if (state->priority < highestPriority){
                highestPriority = state->priority;
                highestPriorityState = state;
            }
        }
        this->isFinal |= state->isFinal;
    }

    this->tokenName = highestPriorityState->tokenName;
}
