#ifndef FANOTREE_H
#define FANOTREE_H

#include <numeric>


#include "binarytree.h"

class FanoTree : public BinaryTree
{

public:

    FanoTree();
    ~FanoTree() = default;
private:

    BinaryTree::TreeNode* build(std::vector<std::pair<QChar, int>> freq) override;

};

#endif // FANOTREE_H
