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
