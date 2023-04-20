/*
Pretty simple BFS, except for the integer overflow (it is trivial in python)
To overcome integer overflow, we subtract the index of the first node in each row,
from every node in that row
*/

#include <vector>
#include <queue>
#include <algorithm>
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

#define ll long long

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        ll answ = 0;
        ll lastL = 0;
        queue<pair<TreeNode*, ll>> q;
        q.push(make_pair(root, 0));

        while(q.size()) {
            int s = q.size();
            ll l = 1LL<<62, r = -1;
            for(int i = 0; i < s; i++) {
                // Pop from queue
                pair<TreeNode*, ll> removed = q.front();
                q.pop();
                TreeNode* u = removed.first;
                ll index = removed.second;
                index -= lastL;

                l = min(l, index);
                r = max(r, index);

                // Explore left and right
                if (u->left) q.push(make_pair(u->left, index*2));
                if (u->right) q.push(make_pair(u->right, index*2+1));
            }
            answ = max(answ, r-l+1);
            cout << answ << endl;
            lastL = l;
        }
        return answ;
    }
};