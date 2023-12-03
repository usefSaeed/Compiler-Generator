//
// Created by deffo on 01/12/23.
//

#ifndef COMPILER_NFA_H
#define COMPILER_NFA_H


#include "../RulesParser/RegularExpression.h"
#include "State.h"
#include <stack>
#include "../Util/Util.h"

class NFA {
    private:
        std::stack<std::stack<State*>> nfaStack;
        std::stack<std::stack<std::string>> disjunctionStack;

        static void addSymbolTransition(State* from, char symbol, State* to);
        void concatenate();
        void disjunction();
        void kleeneClosure();
        void positiveClosure();
        void rebaseStacks();
        void initializeStacks();

    public:
        NFA();
        static void addEpsilonTransition(State* from, State* to);
        std::pair<State*, State*> convertToNfa(std::string regex, std::string tokenName, int priority);

};


#endif //COMPILER_NFA_H
