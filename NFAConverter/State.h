//
// Created by deffo on 01/12/23.
//

#ifndef COMPILER_STATE_H
#define COMPILER_STATE_H

#include <vector>
#include <unordered_set>
#include "Transition.h"

class Transition;

class State {
public:
    std::vector<Transition> transitions;
    bool isFinal;
    std::string tokenName;
    int priority{};
    State();
    explicit State(const std::string& tokenName);
    explicit State(std::unordered_set<State*> states);
    void addTransition(Transition transition);
    State* moveTo(char input);
};


#endif //COMPILER_STATE_H
