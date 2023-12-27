//
// Created by deffo on 24/12/23.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H



#include "Common.h"
#include "ParsingTree.h"
#include "ParsingTableEntry.h"
#include "../Common/NonTerminal.h"
#include "../GrammarParser/Grammar.h"
#include "../../LexicalPhase/NFAConverter/NFACombiner.h"

class Parser {
    private:
        Grammar grammar;
        std::vector<NonTerminal*> NTs;
        std::unordered_map<std::pair<NonTerminal*,std::string>, ParsingTableEntry, PairHash, PairEqual> parsingTable;
        void computeNTsWithFirstSet();
        void computeNTsWithFollowSet();
        void constructParseTable();
    public:
        Parser(Grammar& grammar);
        //ParsingTree parse(std::vector<Token>& input);

};

#endif //COMPILER_PARSER_H
