#ifndef COMPILER_PARSING_RESULT_H
#define COMPILER_PARSING_RESULT_H

#include "ParsingTree.h"
#include "ParsingTrace.h"
#include <iomanip>

class ParsingResult {
public:
    ParsingResult(ParsingTree& tree, std::vector<ParsingTrace>& traces);
    ParsingResult();
    ParsingTree tree;
    std::vector<ParsingTrace> traces;
    void printTrace();
    void printStackTrace();
};

#endif