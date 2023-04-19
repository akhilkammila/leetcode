#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int answ = 0;
    pair<int,int> leftRight(TreeNode* curr) {
        int left = 0, right = 0;

        if (curr->left != NULL) left = 1 + leftRight(curr->left).second;
        if (curr->right != NULL) right = 1 + leftRight(curr->right).first;
        answ = max(answ, max(left, right));
        return make_pair(left, right);
    }

    int longestZigZag(TreeNode* root) {
        leftRight(root);
        return answ;
    }
};