//
// Created by Meniem on 28-Nov-23.
//

#include "RegularDefinition.h"
#include "../Util/Util.h"
#include <utility>
#include <iostream>

RegularDefinition::RegularDefinition() = default;

const std::string &RegularDefinition::getName() const {
    return name;
}

const std::string &RegularDefinition::getRegex() const {
    return regex;
}

RegularDefinition::RegularDefinition(std::string name, std::string regex) : name(std::move(name)), regex(std::move(regex)) {}

void RegularDefinition::standardizeRegex() {
    std::cout << "In Standardize Regex Function" << "\n";
    regex = regex + "    Standardized";
    removeConsecutiveSpaces(regex);
}


