//
// Created by deffo on 02/12/23.
//

#ifndef COMPILER_NFACOMBINER_H
#define COMPILER_NFACOMBINER_H

#include "../RulesParser/RegularExpression.h"
#include "State.h"
#include "NFA.h"
#include <unordered_map>

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

class NFACombiner {
    private:
        State* completeNfa;

    public:
        NFACombiner(std::vector<RegularExpression>&);
        std::unordered_map<std::pair<State*, char>, std::vector<State*>, PairHash, PairEqual> extractTableRepresentation();
        State* getCompleteNfa();

};

#endif //COMPILER_NFACOMBINER_H
