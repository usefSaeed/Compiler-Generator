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

#include <sstream>

struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

struct PairEqual {
    template <typename T1, typename T2>
    bool operator()(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

class Parser {
    private:
        Symbol* startingSymbol;
        Grammar grammar;
        std::vector<NonTerminal*> NTs;
        std::unordered_map<std::pair<NonTerminal*,std::string>, ParsingTableEntry, PairHash, PairEqual> parsingTable;
        void computeNTsWithFirstSet();
        void computeNTsWithFollowSet();
        void constructParseTable();
    public:
        Parser(Grammar& grammar);
        ParsingResult parse(std::vector<Token>& input);
        // for debugging purposes
        Parser(Symbol* symbol, std::unordered_map<std::pair<NonTerminal*,std::string>, ParsingTableEntry, PairHash, PairEqual>& parsingTable);
};

#endif //COMPILER_PARSER_H
