//
// Created by usef on 12/6/2023.
//

#ifndef COMPILER_LAOUTPUT_H
#define COMPILER_LAOUTPUT_H


#include <string>
#include "STRow.h"
#include "SyntaxError.h"
#include "LATrace.h"
#include <vector>

class LAOutput {
private:
    std::vector<STRow> symbolTable;
    std::vector<SyntaxError> errors;
    std::vector<LATrace> trace;


public:
    LAOutput(std::vector<STRow> symbolTable, std::vector<SyntaxError> errors,
             std::vector<LATrace> trace);
    friend std::ostream& operator<<(std::ostream& os, const LAOutput& lao);

    const std::vector<STRow> &getSymbolTable() const;

    const std::vector<SyntaxError> &getErrors() const;

    const std::vector<LATrace> &getTrace() const;

};


#endif //COMPILER_LAOUTPUT_H
