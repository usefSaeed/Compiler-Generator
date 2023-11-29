//
// Created by Meniem on 28-Nov-23.
//

#ifndef COMPILER_REGULAREXPRESSION_H
#define COMPILER_REGULAREXPRESSION_H

#include <string>
#include "RegularDefinition.h"

class RegularExpression : public RegularDefinition {

    private:
        std::string name;
        std::string regex;
        int priority{};

    public:
    RegularExpression();

    [[nodiscard]] std::string toString() const;

    [[nodiscard]] int getPriority() const;

    RegularExpression(std::string name, std::string regex, int priority);
};


#endif //COMPILER_REGULAREXPRESSION_H
