//
// Created by usef on 12/4/2023.
//

#ifndef COMPILER_STROW_H
#define COMPILER_STROW_H

#include <string>

class STRow {
private:
    std::string token;
    std::string tokenType;


public:
    STRow(std::string token,std::string tokenType);
    friend std::ostream& operator<<(std::ostream& os, const STRow& strow);

    [[nodiscard]] const std::string &getToken() const;

    [[nodiscard]] const std::string &getTokenType() const;
};

#endif //COMPILER_STROW_H
