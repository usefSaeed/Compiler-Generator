//
// Created by usef on 12/6/2023.
//

#include "LAOutput.h"

#include <utility>
#include "iostream"


LAOutput::LAOutput(std::vector<STRow> symbolTable, std::vector<SyntaxError> errors,
                   std::vector<LATrace> trace) : symbolTable(std::move(symbolTable)),
                   errors(std::move(errors)), trace(std::move(trace)) {}

std::ostream &operator<<(std::ostream &os, const LAOutput &lao) {
    os << "<<<TRACE>>>\n";
    for (const auto& t: lao.trace)
        os << t;
    os << "<<<SYMBOL TABLE>>>\n";
    for (const auto& s: lao.symbolTable)
        os << s;
    os << "<<<Syntax Errors>>>\n";
    for (const auto& e: lao.errors)
        os << e;
    return os;
}

const std::vector<STRow> &LAOutput::getSymbolTable() const {
    return symbolTable;
}

const std::vector<SyntaxError> &LAOutput::getErrors() const {
    return errors;
}

const std::vector<LATrace> &LAOutput::getTrace() const {
    return trace;
}

