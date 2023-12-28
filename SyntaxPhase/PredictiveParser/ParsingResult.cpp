#include "ParsingResult.h"

ParsingResult::ParsingResult(ParsingTree& tr, std::vector<ParsingTrace>& trc)
    : tree(tr), traces(trc) {};
    
ParsingResult::ParsingResult() {};

void ParsingResult::printTrace() {
    std::vector<std::string> stackStrings;
    std::vector<std::string> inputStrings;
    int maxStackLength = 0;
    int maxInputLength = 0;
    
    for (auto& trace: traces) {
        auto stackString = trace.stackString();
        auto inputString = trace.inputString();
        stackStrings.push_back(stackString);
        inputStrings.push_back(inputString);
        
        maxStackLength = std::max(maxStackLength, (int) stackString.length());
        maxInputLength = std::max(maxInputLength, (int) inputString.length());
    }
    
    std::cout << std::setw(maxStackLength) << "Stack" << "\t" 
              << std::setw(maxInputLength) << "Input" << "\n";
    
    for (int i=0; i < traces.size(); i++) {
        std::cout << std::setw(maxStackLength) << stackStrings[i] << "\t";
        std::cout << std::setw(maxInputLength) << inputStrings[i] << "\t";
        std::cout << traces[i].extrasString() << std::endl;
    }

    std::cout << std::endl;
}
