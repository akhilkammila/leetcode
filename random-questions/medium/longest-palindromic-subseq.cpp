#include <string>
#include <iostream>
#include <vector>
using namespace std;

#define endl '\n'
#define ll long long
#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#include </Users/akhilkammila/Competitive Programming/debug.h>
#else
#define DEBUG(...) 47;
#endif

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));

        for(int i = 0; i < s.size(); i++) dp[i][i] = 1;

        for(int offset = 1; offset<s.size(); offset++) {
            for(int i = 0; i < s.size()-offset; i++) {
                int j = i + offset; //end digit

                // recurrence
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                if (s[i] == s[j]) dp[i][j] = 2 + dp[i+1][j-1];
            }
        }
        return dp[0][s.size()-1];
    }
};

int main() {
    string s = "cbbds";
    Solution sol;
    cout << sol.longestPalindromeSubseq(s);
}