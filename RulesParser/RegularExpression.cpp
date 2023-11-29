//
// Created by Meniem on 28-Nov-23.
//

#include "RegularExpression.h"

RegularExpression::RegularExpression(std::string name, std::string regex, int priority)
: RegularDefinition(std::move(name), std::move(regex)), priority(priority) {}

RegularExpression::RegularExpression() = default;


int RegularExpression::getPriority() const {
    return priority;
}
