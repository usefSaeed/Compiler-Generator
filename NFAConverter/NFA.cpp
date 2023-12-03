//
// Created by deffo on 01/12/23.
//

#include "NFA.h"

NFA::NFA() = default;

void NFA::addEpsilonTransition(State* from, State* to) {
    Transition transition('\0', to);
    from->addTransition(transition);
}

void NFA::addSymbolTransition(State* from, char symbol, State* to){
    Transition transition(symbol, to);
    from->addTransition(transition);
}

void NFA::concatenate(){
    if (nfaStack.top().size() == 2){ return;}

    State* end2 = nfaStack.top().top();
    nfaStack.top().pop();
    State* start2 = nfaStack.top().top();
    nfaStack.top().pop();

    State* end1 = nfaStack.top().top();
    nfaStack.top().pop();
    State* start1 = nfaStack.top().top();
    nfaStack.top().pop();

    addEpsilonTransition(end1, start2);
    nfaStack.top().push(start1);
    nfaStack.top().push(end2);
}

void NFA::disjunction() {
    State* end2 = nfaStack.top().top();
    nfaStack.top().pop();
    State* start2 = nfaStack.top().top();
    nfaStack.top().pop();

    State* end1 = nfaStack.top().top();
    nfaStack.top().pop();
    State* start1 = nfaStack.top().top();
    nfaStack.top().pop();

    State* initial = new State();  // New initial state
    addEpsilonTransition(initial, start1);
    addEpsilonTransition(initial, start2);
    State* final = new State(); // New final state
    addEpsilonTransition(end1, final);
    addEpsilonTransition(end2, final);
    nfaStack.top().push(initial);
    nfaStack.top().push(final);
}

void NFA::kleeneClosure(){
    State* end = nfaStack.top().top();
    nfaStack.top().pop();
    State* start = nfaStack.top().top();
    nfaStack.top().pop();

    State* initial = new State(); // New initial state
    State* final = new State(); // New final state
    addEpsilonTransition(initial, start);
    addEpsilonTransition(end, final);
    addEpsilonTransition(initial, final);
    addEpsilonTransition(final, initial);
    nfaStack.top().push(initial);
    nfaStack.top().push(final);
}

void NFA::positiveClosure(){
    State* end = nfaStack.top().top();
    nfaStack.top().pop();
    State* start = nfaStack.top().top();
    nfaStack.top().pop();

    State* initial = new State(); // New initial state
    State* final = new State(); // New final state
    addEpsilonTransition(initial, start);
    addEpsilonTransition(end, final);
    addEpsilonTransition(final, initial);
    nfaStack.top().push(initial);
    nfaStack.top().push(final);
}

void NFA::rebaseStacks(){
    State* bracketsEnd = nfaStack.top().top();
    nfaStack.top().pop();
    State* bracketsStart = nfaStack.top().top();
    nfaStack.top().pop();

    nfaStack.pop();     // pop the brackets stack
    nfaStack.top().push(bracketsStart);
    nfaStack.top().push(bracketsEnd);
}

void NFA::initializeStacks(){
    std::stack<State*> initialNfaStack;
    nfaStack.push(initialNfaStack);
    std::stack<std::string> initialDisjunctionStack;
    disjunctionStack.push(initialDisjunctionStack);
}

std::pair<State*, State*> NFA::convertToNfa(std::string regex, std::string tokenName, int priority) {
    initializeStacks();
    for (int i = 0; i < regex.size(); i++) {
        char symbol = regex[i];
        if (symbol == '|') {
            disjunctionStack.top().push(std::string("|"));
        } else if (symbol == '(') {
            std::stack<State*> bracketsNfaStack;
            nfaStack.push(bracketsNfaStack);
            std::stack<std::string> bracketsDisjunctionStack;
            disjunctionStack.push(bracketsDisjunctionStack);
        } else if (symbol == ')') {
            disjunctionStack.pop();
            if (regex[i+1] == '*'){
                kleeneClosure();
                i++;
            } else if (regex[i+1] == '+') {
                positiveClosure();
                i++;
            }
            rebaseStacks();
            if ((not disjunctionStack.empty()) and (not disjunctionStack.top().empty()) and disjunctionStack.top().top() == "|"){
                disjunction();
            } else {
                concatenate();
            }
        } else{
            // Skip character
            if (symbol == '\\'){
                symbol = regex[i+1];
                // Epsilon transition entered through the rules
                if (symbol == 'L'){
                    symbol = '\0';
                }
                i++;
            }

            State* start = new State();
            State* end = new State();
            addSymbolTransition(start, symbol, end);
            nfaStack.top().push(start);
            nfaStack.top().push(end);
            concatenate();
        }
    }

    State* nfaEnd = nfaStack.top().top();
    nfaEnd->isFinal = true;
    nfaEnd->tokenName = tokenName;
    nfaEnd->priority = priority;
    nfaStack.top().pop();
    State* nfaStart = nfaStack.top().top();
    std::pair<State*, State*>regexNfa(nfaStart, nfaEnd);
    return regexNfa;
}

