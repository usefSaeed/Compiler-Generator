//
// Created by Meniem on 29-Nov-23.
//

#ifndef COMPILER_RULESCONVERTER_H
#define COMPILER_RULESCONVERTER_H

#include <string>
#include <vector>
#include "RegularExpression.h"


class RulesConverter {
    private:
        std::string filePath;
        static int linesCounter;
        std::vector<RegularExpression> regularExpressions;
        std::vector<RegularDefinition> regularDefinitions;
        static bool isRegularDefinition(std::string str);
        static bool isRegularExpression(std::string str);
        std::vector<std::string> allKeywords;
        std::vector<std::string> allPunctuation;
        void keywordsHandler(std::string str);
        void punctuationHandler(std::string str);
        [[nodiscard]] int regularDefinitionHandler(std::string str);
        [[nodiscard]] int regularExpressionHandler(std::string str);

    public:
        static constexpr int KEYWORDS = 0;
        static constexpr int PUNCTUATION = 1;
        static constexpr int REGULAR_DEFINITION = 2;
        static constexpr int REGULAR_EXPRESSION = 3;
        [[nodiscard]] const std::vector<RegularExpression> &getRegularExpressions() const;
        explicit RulesConverter(std::string filePath);
        [[nodiscard]] static int checkType(std::string str);
        [[nodiscard]] int parseFile();

};

#endif //COMPILER_RULESCONVERTER_H
