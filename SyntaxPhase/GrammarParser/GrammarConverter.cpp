//
// Created by Meniem on 19-Dec-23.
//

#include "GrammarConverter.h"
#include <iostream>
#include <fstream>
#include <map>
#include "../../Util/Util.h"

int GrammarConverter::definitionCounter;

GrammarConverter::GrammarConverter() = default;

int GrammarConverter::parseFile(const std::string& filePath) {
    // Need to Run Validation as one pass to get Non-Terminal Definitions, so we can later detect
    // when Non-Terminal are used without definition and catch those errors.
    std::ifstream file(filePath);
    if (!file.is_open()){
        std::cerr << "Unable to open file." << "\n";
        return -1;
    }

    std::string nonTerminalDefinition;
    while(getline(file, nonTerminalDefinition, '#')) {
        trimBlanksFromEnds(nonTerminalDefinition);
        if (nonTerminalDefinition.empty())
            continue;  // Ignores empty Lines
        definitionCounter++;

        int status = validateGrammar(nonTerminalDefinition);
        if (status == -1) return -1;

    }
    file.close();

    definitionCounter = 0;

    file.open(filePath);
    if (!file.is_open()){
        std::cerr << "Unable to open file." << "\n";
        return -1;
    }

    while(getline(file, nonTerminalDefinition, '#')) {
        trimBlanksFromEnds(nonTerminalDefinition);
        if (nonTerminalDefinition.empty())
            continue;  // Ignores empty Lines
        definitionCounter++;

        std::vector<std::string> definitionSides = splitWithStringDelimiter(nonTerminalDefinition, "::=");
        std::string nonTerminalName = definitionSides[0];
        std::string nonTerminalProductions = definitionSides[1];
        trimBlanksFromEnds(nonTerminalName);
        removeConsecutiveSpaces(nonTerminalName);

        int status = findTerminals(nonTerminalProductions);
        if (status == -1) return -1;

        removeConsecutiveSpaces(nonTerminalProductions);
        trimBlanksFromEnds(nonTerminalProductions);

        status = parseProductions(nonTerminalName, nonTerminalProductions);
        if (status == -1) return -1;

    }
    file.close();

    return 0;
}


const std::unordered_set<std::string> &GrammarConverter::getTerminals() const {
    return terminals;
}

const std::vector<NonTerminalSymbol> &GrammarConverter::getNonTerminals() const {
    return nonTerminals;
}

 int GrammarConverter::validateGrammar(const std::string& definition) {


    // Handles definitions where there is a wrong number of separator either none or more than one.
    std::vector<std::string> definitionSides = splitWithStringDelimiter(definition, "::=");
    if (definitionSides.size() < 2){
        std::cerr << "Definition Number: " << definitionCounter << " does not have correct definition separator." << "\n";
        return -1;
    }

    if (definitionSides.size() > 2){
        std::cerr << "Definition Number: " << definitionCounter << " has multiple definition separators." << "\n";
        return -1;
    }

    std::string nonTerminalName = definitionSides[0];
    std::string nonTerminalProductions = definitionSides[1];
    trimBlanksFromEnds(nonTerminalName);
    trimBlanksFromEnds(nonTerminalProductions);

    // Handles definitions where either side is empty or blank.
    if (nonTerminalName.empty()){
        std::cerr << "Definition Number: " << definitionCounter << " Definition Name is blank." << "\n";
        return -1;
    }

    if (nonTerminalProductions.empty()){
        std::cerr << "Definition Number: " << definitionCounter << " Definition Production is blank." << "\n";
        return -1;
    }

    // Checks if Non-Terminal was defined Before.
    if (nonTerminalNames.contains(nonTerminalName)){
        std::cerr << "Definition: " << nonTerminalName << " is defined twice." << "\n";
        return -1;
    }

    nonTerminalNames.insert(nonTerminalName);

    return 0;
}

int GrammarConverter::findTerminals(std::string& productions) {
    // accumulates terminal symbols if they exist
    std::string accumulator;
    for(int i = 0; i < productions.size(); i++){
        char c = productions[i];
        // check if single quote is found with no escape character before it.
        if (c == '\'' && productions[i-1] != '\\'){
            // Delete the quotes.
            productions.replace(i, 1, " ");
            i++;
            // loop until another quote symbol is found that doesn't have an escape character before.
            while ( (productions[i] != '\'' || productions[i-1] == '\\')){
                // handle a single quote that is not closed.
                if (i == productions.size()){
                    std::cerr << "Definition Number: " << definitionCounter << " Quote is not closed." << "\n";
                    return -1;
                }
                // Skip the escape character, so it can be put into the terminals set with its appropriate name
                if (productions[i] == '\\'){
                    i++;
                    continue;
                }
                accumulator += productions[i];
                i++;
            }
            // Delete the quotes.
            productions.replace(i, 1, " ");
        }
        if (!accumulator.empty()){
            terminals.insert(accumulator);
            accumulator.clear();
        }
    }
    return 0;
}

int GrammarConverter::parseProductions(const std::string& nonTerminalName, std::string &productions) {
    productionsVector result;
    // Replace any escaped conjunction, so we can split using conjunction without errors.
    replaceAll(productions, "\\|", "\\$");
    std::vector<std::string> delimitedProductions = split(productions, '|');
    for (std::string& production : delimitedProductions){
        // return the string to original by replacing the replacement string that was used above by the original escaped conjunction
        replaceAll(production, "\\$", "\\|");
        trimBlanksFromEnds(production);
        removeConsecutiveSpaces(production);
        // split by spaces to get each symbol in each production.
        std::vector<std::string> splitProduction = split(production, ' ');
        for (std::string& symbol : splitProduction){
            if (symbol != "\\L"){
                // if symbol is escaped then remove the escape character to correctly compare with the terminals set
                if (symbol[0] == '\\')
                    symbol.erase(symbol.begin());
                // if it is a Non-Terminal that was not defined before then throw an error.
                // This part is what enforced a one time pass for validation, so we can get all the defined Non-Terminals
                // As you can define Non-Terminals in any order, so you can't move sequentially.
                if (!terminals.contains(symbol) && !nonTerminalNames.contains(symbol)){
                    std::cerr << "Definition Number: " << definitionCounter << " Non-Terminal ("  << symbol << ") is not defined."<< "\n";
                    return -1;
                }
            }
        }
        result.push_back(splitProduction);
    }
    // Create our new Non-Terminal and place it in our Non-Terminals Vector.
    nonTerminals.emplace_back(nonTerminalName, result);
    return 0;
}

bool GrammarConverter::leftFactor() {
    bool appliedLeftFactoring = false; // Flag to check if there is a left factoring to eliminate in our grammar or not.
    std::vector<NonTerminalSymbol> temporaryNonTerminals;
    int originalNonTerminalIndex = 0;
    temporaryNonTerminals.push_back(nonTerminals[0]);
    for (int i = 0; i < temporaryNonTerminals.size(); i++){
        auto productions = temporaryNonTerminals[i].getProductions();
        std::map<std::string, std::vector<int>> factoringMap; // create a factoring map where each beginning symbol of the productions gets an entry with the places it occurred as values.
        // Loop over all productions and get the starting symbol of each production and check if it was repeated.
        for (int index = 0; index < productions.size(); index++){
            // If it's the first time we encounter this symbol then add it to the factoring map with just one index
            if (!factoringMap.contains(productions[index][0])){
                std::vector<int> factorIndices = {index};
                factoringMap.insert({productions[index][0], factorIndices});
            }
                // If it was found in the factoring map then add the other index where it was found, and now we know left factoring is present in our grammar.
            else {
                auto it = factoringMap.find(productions[index][0]);
                (it->second).push_back(index);
                appliedLeftFactoring = true;
            }
        }

        bool nonTerminalsFactored = false; // flag to check if we factor this Non-Terminal
        int factorCounter = 1; // number to distinguish names of factored expressions
        productionsVector factoredProductions;
        productionsVector editedFactoredProductions;
        std::string  newNonTerminalName;
        // Loop over the factoringMap to check the ones who are repeated.
        for(auto factor : factoringMap){
            // If 2 productions have a common starting symbol (factor).
            if (factor.second.size() > 1){
                nonTerminalsFactored = true;
                // Edit the current production : A  -> aA`
                newNonTerminalName = temporaryNonTerminals[i].getName()+ std::to_string(factorCounter);
                editedFactoredProductions.push_back(std::vector<std::string>{factor.first, newNonTerminalName});
                // Loop over all the indices where the factor was common to create the new Non-Terminal.
                for (int j : factor.second){
                    std::vector<std::string> temporaryProduction;
                    // Loop over each symbol after the first symbol and add it to our temporary production.
                    for (int k = 1; k < productions[j].size(); k++){
                        temporaryProduction.push_back(productions[j][k]);
                    }
                    // Handle cases where factor has nothing after it, we add an epsilon in the new Non-Terminal.
                    if (temporaryProduction.empty())
                        temporaryProduction.emplace_back("\\L");

                    factoredProductions.push_back(temporaryProduction);
                }
                // Add the new NonTerminal to the productions.
                auto newNonTerminal = NonTerminalSymbol(newNonTerminalName, factoredProductions);
                temporaryNonTerminals.push_back(newNonTerminal);
                nonTerminalNames.insert(newNonTerminalName);
                factoredProductions.clear();

                factorCounter++;
            }
                // If no two productions have the same factor just add the same original productions.
            else{
                std::vector<std::string> temporaryProduction;
                int originalIndex = factor.second[0];
                for (const auto& element : productions[originalIndex])
                    temporaryProduction.push_back(element);
                editedFactoredProductions.push_back(temporaryProduction);
            }
        }
        // If the Non-Terminal was factored then we edit the original production the new one.
        if (nonTerminalsFactored)
            temporaryNonTerminals[i].setProductions(editedFactoredProductions);

        // Check if it was not factored, and we have not processed each element in our original Non-Terminal Vector and add a new one to our temporary vector.
        if (!nonTerminalsFactored && originalNonTerminalIndex < nonTerminals.size() - 1){
            originalNonTerminalIndex++;
            temporaryNonTerminals.push_back(nonTerminals[originalNonTerminalIndex]);
        }
    }
    // Update our Non-Terminals vector with the new one.
    nonTerminals = temporaryNonTerminals;

    return appliedLeftFactoring;
}

bool GrammarConverter::eliminateLeftRecursion() {
    bool hasLeftRecursion = false;
    std::vector<NonTerminalSymbol> newNonTerminals;
    // loop over each Non-Terminal
    for (int i = 0; i < nonTerminals.size(); i++){
        // We need this because we will constantly edit its productions.
        NonTerminalSymbol currentNonTerminal = nonTerminals[i];
        // loop over all Non-Terminals above it.
        for (int j = 0; j < i; j++)
            // Recursively substitute each Non-Terminal combination (if it exists) with our current Non-Terminal.
            currentNonTerminal = substitute(currentNonTerminal, nonTerminals[j]);
        // If after substituting immediate left recursion is found.
        if (hasImmediateLeftRecursion(currentNonTerminal)){
            hasLeftRecursion = true;
            std::vector<NonTerminalSymbol> modifiedNonTerminals = eliminateImmediateLeftRecursion(currentNonTerminal);
            // Push the modified Non-Terminals to our new Non-Terminals vector.
            for (const auto& nonTerminal : modifiedNonTerminals){
                newNonTerminals.push_back(nonTerminal);
                nonTerminalNames.insert(nonTerminal.getName());
            }

        }
            // If no Immediate left recursion is found then just add the original Non-Terminal.
        else {
            newNonTerminals.push_back(nonTerminals[i]);
        }

    }
    // Update our Non-Terminals vector with the new one.
    nonTerminals = newNonTerminals;
    return hasLeftRecursion;
}


bool GrammarConverter::hasImmediateLeftRecursion(const NonTerminalSymbol& nonTerminal) {
    // loop over each production in the Non-Terminal
    auto productions = nonTerminal.getProductions();
    for (auto production : productions){
        // Check if the first symbol of a production is the same name of the Non-Terminal
        if (production[0] == nonTerminal.getName())
            return true;
    }
    return false;
}

NonTerminalSymbol GrammarConverter::substitute(const NonTerminalSymbol& currentNonTerminal, const NonTerminalSymbol& potentiallySubstitutedNonTerminal) {
    productionsVector result;
    productionsVector currentProductions = currentNonTerminal.getProductions();
    productionsVector potentiallySubstitutedProductions = potentiallySubstitutedNonTerminal.getProductions();

    for (auto currentProduction : currentProductions){
        // if current production's first symbol doesn't match our potential symbol then just do nothing (add the same production to the result vector)
        if (currentProduction[0] != potentiallySubstitutedNonTerminal.getName())
            result.push_back(currentProduction);
        else {
            // else if it matches then substitute for every production and push into the result vector.
            for (const auto& potentiallySubstitutedProduction : potentiallySubstitutedProductions){
                std::vector<std::string> tempProduction(potentiallySubstitutedProduction);
                for (int i = 1; i < currentProduction.size(); i++)
                    tempProduction.push_back(currentProduction[i]);

                result.push_back(tempProduction);
            }
        }
    }
    NonTerminalSymbol newNonTerminal(currentNonTerminal.getName(), result);
    return newNonTerminal;
}

std::vector<NonTerminalSymbol> GrammarConverter::eliminateImmediateLeftRecursion(const NonTerminalSymbol& nonTerminal) {
    productionsVector alphas;
    productionsVector betas;
    productionsVector productions = nonTerminal.getProductions();
    std::string modifiedName = nonTerminal.getName() + "`";
    // loop over all productions to get each local alpha or beta
    for (auto production : productions){
        std::vector<std::string> localAlpha;
        std::vector<std::string> localBeta;
        // check if first symbol of production equals the Non-Terminal name.
        if (production[0] == nonTerminal.getName()){
            // If yes then it's alpha then we add all symbols after the first one then the modified name.
            for (int i = 1; i < production.size(); i++)
                localAlpha.push_back(production[i]);
            localAlpha.push_back(modifiedName);
            alphas.push_back(localAlpha);
        }
        else {
            // If no then it's beta then we add all the symbols and after them the modified name.
            for (const auto & symbol : production)
                localBeta.push_back(symbol);
            localBeta.push_back(modifiedName);
            betas.push_back(localBeta);
        }
    }
    // Add epsilon transition to alphas (modified Non-Terminal)
    alphas.push_back(std::vector<std::string>{"\\L"});
    // Construct our pair of resulting Non-Terminals
    std::vector<NonTerminalSymbol> result = {NonTerminalSymbol(nonTerminal.getName(), betas), NonTerminalSymbol(modifiedName, alphas)};
    return result;
}