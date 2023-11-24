#include <iostream>
#include <vector>
#include "util.h"

int main() {
    std::vector<std::string> words = split("This is a test string.", ' ');
    for (const std::string& word : words)
        std::cout << word << "\n";

    words = splitWithStringDelimiter("A => A + B  B => B + C  C => C + D", "=>");
    for (const std::string& word : words)
        std::cout << word << "\n";
    return 0;
}