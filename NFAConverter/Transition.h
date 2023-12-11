//
// Created by deffo on 01/12/23.
//

#ifndef COMPILER_TRANSITION_H
#define COMPILER_TRANSITION_H

#include <string>
#include "State.h"

class State;

class Transition {
    private:
        char input;
        State* nextState;


    public:
        Transition(char input, State* nextState);

        [[nodiscard]] char getInput() const;
        [[nodiscard]] State* getNextState() const;


};

#endif //COMPILER_TRANSITION_H
