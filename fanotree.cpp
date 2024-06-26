#include "fanotree.h"

FanoTree::FanoTree()
    :BinaryTree()
{

}


BinaryTree::TreeNode* FanoTree::build(std::vector<std::pair<QChar, int>> freq)
{
    auto sum = std::accumulate(freq.begin(), freq.end(), 0, [](int acc, const std::pair<QChar, int>& p) {
        return acc + p.second;
    });

    double half = static_cast<double>(sum) / 2;

    BinaryTree::TreeNode* tree = new BinaryTree::TreeNode();
    tree->value = std::accumulate(freq.begin(), freq.end(), QString(""), [](QString acc, const std::pair<QChar, int>& p) {
        return acc + p.first;
    });

    tree->sum = sum;

    int index = 0;


    int prev = 0;
    int cur = freq[index].second;


    while (static_cast<double>(cur) < half)
    {
        index++;
        prev = cur;
        cur += freq[index].second;
    }


    if (abs(half - static_cast<double>(cur)) < abs(half - static_cast<double>(prev)))
    {
        std::vector<std::pair<QChar, int>> firstPart = {freq.begin(), freq.begin() + index + 1};
        std::vector<std::pair<QChar, int>> secondPart = { freq.begin() + index + 1 , freq.end()};


        tree->left = build(firstPart);
        tree->right = build(secondPart);
    }
    else if(abs(half - static_cast<double>(cur)) == abs(half - static_cast<double>(prev)))
    {
        if (freq.size() == 1)
            return tree;
        std::vector<std::pair<QChar, int>> firstPart = { freq.begin(), freq.begin() + index + 1 };
        std::vector<std::pair<QChar, int>> secondPart = { freq.begin() + index + 1 , freq.end() };


        tree->left = build(firstPart);
        tree->right = build(secondPart);
    }
    else
    {
        if (freq.size() == 1)
            return tree;
        std::vector<std::pair<QChar, int>> firstPart = { freq.begin(), freq.begin() + index };
        std::vector<std::pair<QChar, int>> secondPart = { freq.begin() + index , freq.end() };


        tree->left = build(firstPart);
        tree->right = build(secondPart);
    }

    return tree;



}
