//
// Created by deffo on 01/12/23.
//

#ifndef COMPILER_STATE_H
#define COMPILER_STATE_H

#include <vector>
#include "Transition.h"

class Transition;

class State {
    public:
        std::vector<Transition> transitions;
        bool isFinal;
        std::string tokenName;
        int priority;

        State();
        State(const std::string& tokenName);
        void addTransition(Transition transition);
        State* moveTo(char input);

};


#endif //COMPILER_STATE_H
