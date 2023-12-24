//
// Created by Meniem on 19-Dec-23.
//

#ifndef COMPILER_GRAMMARCONVERTER_H
#define COMPILER_GRAMMARCONVERTER_H

#include <string>

class GrammarConverter {
    private:
    std::string filePath;
    static int definitionCounter;

    public:
    [[nodiscard]] int parseFile();

    explicit GrammarConverter(std::string filePath);
};


#endif //COMPILER_GRAMMARCONVERTER_H
