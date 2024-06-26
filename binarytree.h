#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <QString>

class BinaryTree
{
public:


    struct TreeNode
    {
        TreeNode *right;
        TreeNode *left;

        QString value;
        int32_t sum = 0;
    };


    BinaryTree();
    void create(const QString& text);

    inline TreeNode* getRoot() const {return root; };

    std::vector<std::pair<QChar, int>> makeSortedFreqTable(const QString& text);

    int32_t getHeight() const;
    std::vector<int32_t> getWidthPerLevel() const;


protected:

    virtual BinaryTree::TreeNode* build(std::vector<std::pair<QChar, int>> freq) = 0;

    TreeNode *root = nullptr;

private:
    int32_t getHeight(TreeNode* node) const;
    void getWidthPerLevel(TreeNode* node, std::vector<int>& widths, int32_t level) const;

};

#endif // BINARYTREE_H
