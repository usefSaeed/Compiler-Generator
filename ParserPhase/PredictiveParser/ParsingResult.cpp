#include "ParsingResult.h"

ParsingResult::ParsingResult(ParsingTree& tr, std::vector<ParsingTrace>& trc)
    : tree(tr), traces(trc) {};
    
ParsingResult::ParsingResult() {};

void ParsingResult::printTrace() {
    for (auto& trace: traces) {
        std::cout << trace;
    }
    std::cout << std::endl;
}