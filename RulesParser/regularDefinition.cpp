//
// Created by Meniem on 28-Nov-23.
//

#include "regularDefinition.h"

#include <utility>
#include <iostream>

regularDefinition::regularDefinition() = default;

const std::string &regularDefinition::getName() const {
    return name;
}

const std::string &regularDefinition::getRegex() const {
    return regex;
}

regularDefinition::regularDefinition(std::string name, std::string regex) : name(std::move(name)), regex(std::move(regex)) {}

void regularDefinition::standardizeRegex() {
    std::cout << "In Standardize Regex Function" << "\n";
    regex = regex + " Standardized";
}


