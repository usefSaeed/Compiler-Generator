//
// Created by deffo on 01/12/23.
//

#include "Transition.h"

Transition::Transition(char input, State* nextState) {
    this->input = input;
    this->nextState = nextState;
}

char Transition::getInput() const {
    return input;
}

State* Transition::getNextState() const {
    return nextState;
}




