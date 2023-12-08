//
// Created by usef on 12/4/2023.
//

#include "STGenerator.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <sstream>

STGenerator::STGenerator(DFA &dfa) : dfa(std::move(dfa)) {}

LAOutput STGenerator::execute(const std::string& scriptFilePath){
    std::vector<LATrace> trace;
    std::vector<STRow> symbolTable;
    std::vector<SyntaxError> errors;
    newInputReset();
    readScriptFile(scriptFilePath);
    input += TERMINAL_SYMBOL;
    while (currentCharIdx!=input.size()){
        char c = input[currentCharIdx];
        if (reachedDeadEnd(c)){
            if (noMatchesFoundYet()){
                if (notTerminalSymbol()) {
                    if (isNotSkippable(c)) {
                        SyntaxError e(tokenStartIdx,c);
                        errors.push_back(e);
                    }
                    recover();
                }
            }else{
                currentCharIdx = lastMatchIdx;
                tokenUnlocked(symbolTable);
                trace.emplace_back(LATrace(c,"",true));
            }
        }else{
            currentState = currentState->moveTo(c);
            if (foundMatch()){
                trace.emplace_back(LATrace(c,currentState->tokenName));
                lastMatchIdx = currentCharIdx;
                lastMatchedTokenType = currentState->tokenName;
            }else{
                trace.emplace_back(LATrace(c));
            }
        }
        currentCharIdx ++;
    }
    LAOutput lao = LAOutput(symbolTable, errors, trace);
    std::cout << lao;
    return lao;
}

bool STGenerator::isNotSkippable(char c) {
    if (isspace(c))
        return false;
    return true;
}

void STGenerator::newTokenReset() {
    getStartState();
    lastMatchedTokenType = "";
    tokenStartIdx = lastMatchIdx+1;
    lastMatchIdx = -1;
}

void STGenerator::recover() {
    getStartState();
    tokenStartIdx = currentCharIdx+1;
}


void STGenerator::newInputReset() {
    input = "";
    currentCharIdx = 0;
    newTokenReset();
}

void STGenerator::tokenUnlocked(std::vector<STRow>& symbolTable) {
    STRow strow(input.substr(tokenStartIdx,lastMatchIdx-tokenStartIdx+1),lastMatchedTokenType);
    symbolTable.push_back(strow);
    newTokenReset();
}

bool STGenerator::noMatchesFoundYet() const {
    return lastMatchIdx==-1;
}

bool STGenerator::reachedDeadEnd(char c) {
    return currentState->moveTo(c)== nullptr;
}

void STGenerator::readScriptFile(const std::string &filepath) {
    std::ifstream file(filepath);
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        input = buffer.str();
        file.close();
    } else {
        std::cerr << "Error opening file: " << filepath << std::endl;
    }
}

bool STGenerator::foundMatch() {
    return currentState->isFinal;
}

void STGenerator::getStartState(){
    currentState = dfa.getStartState();
}

bool STGenerator::notTerminalSymbol() {
    return currentCharIdx!=input.size()-1;
}






