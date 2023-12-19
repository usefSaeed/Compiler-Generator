//
// Created by Meniem on 19-Dec-23.
//

#include "GrammarConverter.h"

#include <utility>
#include <iostream>
#include <fstream>
#include "../../Util/Util.h"

int GrammarConverter::definitionCounter;

int GrammarConverter::parseFile() {
    std::ifstream file(filePath);
    if (!file.is_open()){
        std::cerr << "Unable to open file" << "\n";
        return -1;
    }

    std::string nonTerminalDefinition;
    while(getline(file, nonTerminalDefinition, '#')) {
        definitionCounter++;

        if (nonTerminalDefinition.empty())
            continue;  // Ignores empty Lines

        // Handles definitions where there is a wrong number of separator either none or more than one.
        std::vector<std::string> definitionSides = splitWithStringDelimiter(nonTerminalDefinition, "::=");
        if (definitionSides.size() < 2){
            std::cerr << "Definition Number: " << definitionCounter << " does not have correct definition separator" << "\n";
            return -1;
        }

        if (definitionSides.size() > 2){
            std::cerr << "Definition Number: " << definitionCounter << " has multiple definition separators" << "\n";
            return -1;
        }

        std::string nonTerminalName = definitionSides[0];
        std::string nonTerminalProduction = definitionSides[0];
        trimBlanksFromEnds(nonTerminalName);
        trimBlanksFromEnds(nonTerminalProduction);
        
        // Handles definitions where either side is empty or blank.
        if (nonTerminalName.empty()){
            std::cerr << "Definition Number: " << definitionCounter << "Definition Name is blank" << "\n";
            return -1;
        }

        if (nonTerminalProduction.empty()){
            std::cerr << "Definition Number: " << definitionCounter << "Definition Name is blank" << "\n";
            return -1;
        }



    }

    return 0;
}

GrammarConverter::GrammarConverter(std::string filePath) : filePath(std::move(filePath)) {}
