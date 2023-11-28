//
// Created by Meniem on 28-Nov-23.
//

#include "regularExpression.h"

#include <utility>

regularExpression::regularExpression(std::string name, std::string regex, int priority)
: regularDefinition(std::move(name), std::move(regex)), priority(priority) {}

regularExpression::regularExpression() = default;


int regularExpression::getPriority() const {
    return priority;
}
