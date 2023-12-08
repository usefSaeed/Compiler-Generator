//
// Created by usef on 12/4/2023.
//

#ifndef COMPILER_SYNTAXERROR_H
#define COMPILER_SYNTAXERROR_H

#include <string>


class SyntaxError {
private:
    int idx;

public:
    explicit SyntaxError(int st);
    friend std::ostream& operator<<(std::ostream& os, const SyntaxError& se);

};

#endif //COMPILER_SYNTAXERROR_H
