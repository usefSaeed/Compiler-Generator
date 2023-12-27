//
// Created by deffo on 24/12/23.
//

#ifndef COMPILER_PARSINGTREE_H
#define COMPILER_PARSINGTREE_H

#include "Common.h"
#include "../Common/NonTerminal.h"

class ParsingTreeNode {
private:
    Symbol* symbol;
    std::vector<ParsingTreeNode*> children;
public:
    ParsingTreeNode(Symbol* symbol);
    void addChild(ParsingTreeNode* child);
    std::vector<ParsingTreeNode*> getChildren();
    bool isLeaf();
};

class ParsingTree {
private:
    ParsingTreeNode* root;
    void printNode(const std::string& prefix, ParsingTreeNode* node, bool isLast);
public:
    ParsingTree();
    ParsingTree(ParsingTreeNode *r);
    void print();
};

#endif //COMPILER_PARSINGTREE_H
