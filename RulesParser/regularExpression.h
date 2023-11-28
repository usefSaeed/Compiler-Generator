//
// Created by Meniem on 28-Nov-23.
//

#ifndef COMPILER_REGULAREXPRESSION_H
#define COMPILER_REGULAREXPRESSION_H

#include <string>
#include "regularDefinition.h"

class regularExpression : public regularDefinition {

    private:
        std::string name;
        std::string regex;
        int priority{};

    public:
    regularExpression();

    [[nodiscard]] int getPriority() const;

    regularExpression(std::string name, std::string regex, int priority);
};


#endif //COMPILER_REGULAREXPRESSION_H
