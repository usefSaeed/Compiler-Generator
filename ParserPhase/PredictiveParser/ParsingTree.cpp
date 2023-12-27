#include "ParsingTree.h"

ParsingTree::ParsingTree() = default;

ParsingTree::ParsingTree(ParsingTreeNode *r) : root(r){}

void ParsingTree::print() {
    if (root == nullptr) {
        std::cout << "Empty tree";
    } else {
        printNode("", root, true);
    }
}

void ParsingTree::printNode(const std::string& prefix, ParsingTreeNode* node, bool isLast)
{
    if (node == nullptr)
        throw std::invalid_argument("null node is found in the tree");
        
    std::cout << prefix;
    std::cout << (isLast ? "└──" : "├──");
    std::cout << node << std::endl;

    auto children = node->getChildren();        
    for (int i=0; i < children.size(); i++) {
        bool isLastChild = (i == children.size() - 1);
        printNode(prefix + (isLast ? "    " : "│   "), children[i], isLastChild);
    }
}


ParsingTreeNode::ParsingTreeNode(Symbol* s) : symbol(s) {}

void ParsingTreeNode::addChild(ParsingTreeNode* child) {
    this->children.push_back(child);
}

bool ParsingTreeNode::isLeaf() {
    return this->children.empty();
}

std::vector<ParsingTreeNode*> ParsingTreeNode::getChildren() {
    return this->children;
}