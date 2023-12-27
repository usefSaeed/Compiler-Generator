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
        Grammar grammar;
        std::vector<NonTerminal*> NTs;
        std::unordered_map<std::pair<NonTerminal*,std::string>, ParsingTableEntry, PairHash, PairEqual> parsingTable;
        void computeNTsWithFirstSet();
        void computeNTsWithFollowSet();
        void constructParseTable();
    public:
        Parser(Grammar& grammar);
        ParsingTree parse(std::vector<Token>& input);

};

#endif //COMPILER_PARSER_H
