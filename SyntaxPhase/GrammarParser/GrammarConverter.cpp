//
// Created by Meniem on 19-Dec-23.
//

#include "GrammarConverter.h"
#include <iostream>
#include <fstream>
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

const std::vector<NonTerminal> &GrammarConverter::getNonTerminals() const {
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
                // Skip the escape character so it can be put into the terminals set with it's appropriate name
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
    std::vector<std::vector<std::string>> result;
    // Replace any escaped conjunction so we can split using conjunction without errors.
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





