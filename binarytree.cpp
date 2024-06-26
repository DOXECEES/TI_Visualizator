#include "binarytree.h"

BinaryTree::BinaryTree()
{

}


std::vector<std::pair<QChar, int>> BinaryTree::makeSortedFreqTable(const QString& text)
{
    std::map<QChar, int> freq;
    std::map<QChar, int> enterance;

    int index = 0;

    for (auto i : text)
    {
        freq[i]++;

        if (!enterance.count(i))
            enterance[i] = index;

        index++;
    }

    std::vector<std::pair<QChar, int> > vec;
    auto cmp = [&enterance](std::pair<QChar, int> const& a, std::pair<QChar, int> const& b)
    {
        return a.second != b.second ? a.second > b.second : enterance[a.first] < enterance[b.first];
    };

    std::copy(freq.begin(), freq.end(), back_inserter(vec));

    std::sort(vec.begin(), vec.end(), cmp);



    return vec;
}


void BinaryTree::create(const QString& text)
{
    auto freq = BinaryTree::makeSortedFreqTable(text);
    root = build(freq);
}


int32_t BinaryTree::getHeight() const
{
    return getHeight(root);
}

int32_t BinaryTree::getHeight(TreeNode* node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return 1 + std::max(leftHeight, rightHeight);
    }
}

std::vector<int32_t> BinaryTree::getWidthPerLevel() const
{
    std::vector<int32_t> widths;
    getWidthPerLevel(root, widths, 0);
    return widths;
}

void BinaryTree::getWidthPerLevel(TreeNode* node, std::vector<int>& widths, int32_t level) const
{
    if (node == nullptr)
    {
        return;
    }

    if (widths.size() <= level)
    {
        widths.push_back(0);
    }

    widths[level]++;
    getWidthPerLevel(node->left, widths, level + 1);
    getWidthPerLevel(node->right, widths, level + 1);
}
