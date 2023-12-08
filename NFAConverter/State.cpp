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

