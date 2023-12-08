//
// Created by usef on 12/4/2023.
//

#ifndef COMPILER_SYNTAXERROR_H
#define COMPILER_SYNTAXERROR_H

#include <string>


class SyntaxError {
private:
    char c;
    int idx;

public:
    explicit SyntaxError(int st,char c);
    friend std::ostream& operator<<(std::ostream& os, const SyntaxError& se);

};

#endif //COMPILER_SYNTAXERROR_H
