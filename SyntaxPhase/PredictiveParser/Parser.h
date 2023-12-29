//
// Created by deffo on 24/12/23.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H



#include "Common.h"
#include "ParsingTree.h"
#include "ParsingResult.h"
#include "ParsingTableEntry.h"
#include "../Common/NonTerminal.h"
#include "../GrammarParser/Grammar.h"
#include "../../LexicalPhase/NFAConverter/NFACombiner.h"

#include <sstream>

class Parser {
    private:
        Symbol* startingSymbol;
        Grammar grammar;
        std::vector<std::shared_ptr<NonTerminal>> NTs;
        std::unordered_map<std::pair<NonTerminal*,std::string>, ParsingTableEntry, PairHash, PairEqual> parsingTable;
        void computeNTsWithFirstSet();
        void computeNTsWithFollowSet();
        static Production getInputMatchedProduction(const std::vector<std::vector<std::shared_ptr<Symbol>>>& productions, const std::string& input);
        void constructParseTable();
    public:
        Parser(Grammar& grammar);
        ParsingResult parse(std::vector<Token>& input);
        void printParsingTable();
        void writeParsingTableToCSV();
        // for debugging purposes
        Parser(Symbol* symbol, std::unordered_map<std::pair<NonTerminal*,std::string>, ParsingTableEntry, PairHash, PairEqual>& parsingTable);
};

#endif //COMPILER_PARSER_H
