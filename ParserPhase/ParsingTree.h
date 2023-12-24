//
// Created by deffo on 24/12/23.
//

#ifndef COMPILER_PARSINGTREE_H
#define COMPILER_PARSINGTREE_H

#include "Common.h"
#include "Symbol.h"

class ParsingTreeNode
{
private:
    Symbol *symbol;
    std::vector<Symbol *> children;
};

class ParsingTreeLeafNode : ParsingTreeNode
{
private:
    std::string lexeme;
};

class ParsingTree
{
private:
    ParsingTreeNode *root;

public:
    ParsingTree(ParsingTreeNode *r) : root(r){};
    void print();
};

#endif //COMPILER_PARSINGTREE_H
