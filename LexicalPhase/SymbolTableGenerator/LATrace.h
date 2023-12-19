//
// Created by usef on 12/6/2023.
//

#ifndef COMPILER_LATRACE_H
#define COMPILER_LATRACE_H

#include <string>

class LATrace {
private:
    char inputChar;
    std::string tokenName;
    bool isEndOfToken{};

public:
    explicit LATrace(char inputChar);
    explicit LATrace(char inputChar, std::string tokenName, bool isEndOfToken=false);
    friend std::ostream& operator<<(std::ostream& os, const LATrace& lat);
};


#endif //COMPILER_LATRACE_H
