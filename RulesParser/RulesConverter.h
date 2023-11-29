//
// Created by Meniem on 29-Nov-23.
//

#ifndef COMPILER_RULESCONVERTER_H
#define COMPILER_RULESCONVERTER_H

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include "RegularExpression.h"
#include "../Util/Util.h"

class RulesConverter {
    private:
        std::string filePath;
        std::vector<RegularExpression> regularExpressions;
        static bool IsRegularDefinition(std::string str);
        static bool IsRegularExpression(std::string str);

    public:
        static constexpr int KEYWORDS = 0;
        static constexpr int PUNCTUATION = 1;
        static constexpr int REGULAR_DEFINITIONS = 2;
        static constexpr int REGULAR_EXPRESSIONS = 3;
        [[nodiscard]] const std::vector<RegularExpression> &getRegularExpressions() const;
        explicit RulesConverter(std::string filePath);
        [[nodiscard]] static int CheckType(std::string str);
        int ParseFile();

};


#endif //COMPILER_RULESCONVERTER_H
