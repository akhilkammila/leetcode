#include <vector>
#include <iostream>
#include <string>

using namespace std;

#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#include </Users/akhilkammila/Competitive Programming/debug.h>
#else
#define DEBUG(...) 47;
#endif

/*
2d DP, similar to longest common subsequence

Issues:
Overthought the problem, tried doing a n^3 solution where I did a 2d dp for each
"middle point" in the string

Need to think more deeply about simple solutions and make sure the recurrence is as fast as possible
*/

class Solution {
public:
    const int MAXN = 500;

    int getDp(int l, int r, vector<vector<int>>& dp) {
        if (r <= l) return 0; // base case: length 1 or less
        if (l < 0 || r >= dp.size()) return MAXN + 1;
        return dp[l][r];
    }

    int minInsertions(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), MAXN+1));

        for(int size = 1; size <= s.size(); size++) {
            for(int l = 0; l <= s.size() - size; l++) {
                int r = l + size - 1;
                
                dp[l][r] = min(getDp(l+1, r, dp), getDp(l, r-1, dp)) + 1;
                if (s[l] == s[r]) dp[l][r] = getDp(l+1, r-1, dp);
            }
        }
        return dp[0][s.size()-1];
    }
};

int main() {
    Solution s = Solution();
    cout << s.minInsertions("azzazazzzaazazza");
    return 0;
}