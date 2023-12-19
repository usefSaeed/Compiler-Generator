//
// Created by usef on 12/2/2023.
//

#include "DFA.h"

State *DFA::getStartState() {
    return startState;
}

DFA::DFA(State *startState) {
    this->alphabet = getAlphabet(startState);
    this->startState = convertToDFA(startState, alphabet);
}

State* DFA::minimize() {
    std::unordered_set<State*> finalStates;
    std::unordered_set<State*> nonFinalStates;

    std::vector<State*> states = allStates(this->startState);
    for (State* state: states) {
        if (state->isFinal)
            finalStates.insert(state);
        else
            nonFinalStates.insert(state);
    }
    
    std::vector<std::unordered_set<State*>> groups;
    groups.push_back(nonFinalStates);
    
    auto finalStatesGroups = groupByTokenName(finalStates);
    groups.insert(groups.end(), finalStatesGroups.begin(), finalStatesGroups.end());
    
    this->startState = minimize(groups);
    this->transitionTable = createTransitionTable(allStates(this->startState));
    return this->startState;
}

State* DFA::convertToDFA(State* nfaStartState, const std::unordered_set<char>& alphabet) {
    std::stack<std::unordered_set<State*>> unmarked;
    std::unordered_map<std::unordered_set<State*>, State*, StatePtrSetHash, StatePtrSetEquality> mapping;
    
    std::unordered_set<State*> startStates = epsilonClosure(nfaStartState);
    State* dfaStartState = new State(startStates);
    mapping[startStates] = dfaStartState;
    unmarked.push(startStates);
    
    while (!unmarked.empty()) {
        std::unordered_set<State*> T = unmarked.top(); unmarked.pop();
        
        for (char a: alphabet) {
            if (a == EPSILON) continue;

            std::unordered_set<State*> U = epsilonClosure(move(T,a));

            if (U.empty()) continue;

            if (mapping.find(U) == mapping.end()) {
                unmarked.push(U);
                mapping[U] = new State(U);
            }

            Transition transition(a, mapping[U]);
            this->transitionTable[{mapping[T], a}] = mapping[U];
            mapping[T]->addTransition(transition);
        }
    }
    
    return dfaStartState;
}


std::unordered_set<char> getAlphabet(State* startState) {
    std::stack<State*> frontier;
    std::unordered_set<char> symbols;
    std::unordered_set<State*> visited;

    frontier.push(startState);
    while (!frontier.empty()) {
        State* state = frontier.top(); frontier.pop();
        visited.insert(state);

        for (Transition transition: state->transitions) {
            symbols.insert(transition.getInput());

            if (visited.find(transition.getNextState()) == visited.end()) {
                frontier.push(transition.getNextState());
            }
        }
    }

    return symbols;
}

std::unordered_set<State*> epsilonClosure(State* state) {
    std::unordered_set<State*> states;
    if (state == nullptr) return states;

    states.insert(state);
    return epsilonClosure(states);
}

std::unordered_set<State*> epsilonClosure(const std::unordered_set<State*>& states) {
    std::unordered_set<State*> output;
    if (states.empty()) return output;
    
    std::stack<State*> frontier;
    for (State* state: states) 
        frontier.push(state);
    
    while (!frontier.empty()) {
        State* state = frontier.top(); frontier.pop();
        
        if (output.find(state) != output.end())
            continue;

        for (Transition transition: state->transitions) {
            if (transition.getInput() == EPSILON) {
                frontier.push(transition.getNextState());
            }
        }
        
        output.insert(state);
    }
    
    return output;
}


std::unordered_set<State*> move(const std::unordered_set<State*>& states, char symbol) {
    std::unordered_set<State*> nextStates;

    for (State* state: states) {
        for (Transition transition: state->transitions) {
            if (transition.getInput() == symbol) {
                nextStates.insert(transition.getNextState());
            }
        }
    }

    return nextStates;
}

State* DFA::minimize(std::vector<std::unordered_set<State*>> groups) {
    std::unordered_map<State*, int> stateGroup;
    for (int i=0; i < groups.size(); i++) {
        const auto& group = groups[i];
        for (auto &state: group) {
            stateGroup[state] = i;
        }
    }

    bool changed = true;
    while (changed) {
        changed = false;

        for (auto &group: groups) {
            std::unordered_map<State*, int> stateSubGroup;
            std::vector<std::unordered_set<State*>> subGroups;

            for (State* s1: group) {
                if (stateSubGroup.find(s1) != stateSubGroup.end())
                    continue;

                std::unordered_set<State*> tempGroup;
                int groupIndex = subGroups.size();
                tempGroup.insert(s1);
                stateSubGroup[s1] = groupIndex;

                for (State* s2: group) {
                    if (stateSubGroup.find(s2) != stateSubGroup.end())
                        continue;

                    bool distinguishable = false;
                    for (char symbol: alphabet) {

                        if (stateGroup[this->transitionTable[{s1, symbol}]] !=
                            stateGroup[this->transitionTable[{s2, symbol}]])
                        {
                            distinguishable = true;
                            break;
                        }
                    }

                    if (!distinguishable) {
                        tempGroup.insert(s2);
                        stateSubGroup[s2] = groupIndex;
                    }
                }

                subGroups.push_back(tempGroup);
            }

            if (subGroups.size() > 1) {
                groups.erase(std::find(groups.begin(), groups.end(), group));

                for (auto &subGroup: subGroups)
                    groups.push_back(subGroup);

                for (auto kv: stateSubGroup) {
                    stateGroup[kv.first] = kv.second;
                }

                changed = true;
                break;
            }
        }
    }

    State* newStartState;

    // create group representatives
    std::unordered_map<std::unordered_set<State*>, State*, StatePtrSetHash, StatePtrSetEquality> representative;

    for (auto &group: groups) {
        auto r = new State(group);
        representative[group] = r;

        if (group.find(this->startState) != group.end())
            newStartState = r;
    }

    // create transitions between representatives
    for (auto &group: groups) {
        State* s = *(group.begin());

        for (auto& t: s->transitions) {
            std::unordered_set<State*> nextGroup;

            for (auto &g: groups) {
                if (g.find(t.getNextState()) != g.end()) {
                    nextGroup = g;
                    break;
                }
            }

            Transition transition(t.getInput(), representative[nextGroup]);
            representative[group]->addTransition(transition);
        }
    }

    return newStartState;
}

std::vector<State*> allStates(State* startState) {
    std::vector<State*> states;
    std::stack<State*> frontier;
    std::unordered_map<State*, int> visited;
    frontier.push(startState);
    while(not frontier.empty()){
        State* currentState = frontier.top();
        frontier.pop();
        if(visited.find(currentState) != visited.end()){
            continue;
        }
        visited[currentState] = 1;
        for(Transition transition: currentState->transitions){
            frontier.push(transition.getNextState());
        }
        states.push_back(currentState);
    }
    return states;
}

TransitionTable createTransitionTable(const std::vector<State*> &states) {
    TransitionTable  transitionTable;
    for (State* state: states) {
        for (Transition transition: state->transitions) {
            char symbol = transition.getInput();
            transitionTable[{state, symbol}] = transition.getNextState();
        }
    }
    return transitionTable;
}

std::vector<std::unordered_set<State*>> groupByTokenName(std::unordered_set<State*> finalStates) {
    std::unordered_map<std::string,std::unordered_set<State*>> tokenGroup;
    for (auto& state: finalStates) 
        tokenGroup[state->tokenName].insert(state);
    
    std::vector<std::unordered_set<State*>> groups;
    for (auto& tokenGroupPair: tokenGroup) 
        groups.push_back(tokenGroupPair.second);
        
    return groups;
}