#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

#define endl '\n'
#define ll long long
#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#include </Users/akhilkammila/Competitive Programming/debug.h>
#else
#define DEBUG(...) 47;
#endif

const ll MODULO = 1e9+7;

class Solution {
public:

    int numWays(vector<string>& words, string target) {
        // Find width of dp array (max length of a word)
        int maxWordLength = 0;
        for(string s : words) {
            maxWordLength = max(maxWordLength, (int)s.size());
        }

        // Setup dp array
        vector<vector<ll>> dp(target.size() + 1, vector<ll>(maxWordLength + 1));
        for(int i = 0; i < maxWordLength + 1; i++) dp[0][i] = 1;
        for(int i = 1; i < target.size() + 1; i++) dp[i][0] = 0;

        // Find number of characters at each position
        vector<vector<int>> counts(26, vector<int>(maxWordLength));
        for(string s : words) {
            for(int i = 0; i < s.size(); i++) {
                counts[s[i] - 'a'][i] += 1;
            }
        }

        // Dp recurrence
        for(int t = 1; t < target.size() + 1; t++) {
            for(int c = 1; c < maxWordLength + 1; c++) {
                dp[t][c] = (dp[t][c-1] + dp[t-1][c-1] * counts[target[t-1]-'a'][c-1]) % MODULO;
            }
        }
        return dp[target.size()][maxWordLength];
    }
};

int main() {
    string target = "aba";
    vector<string> words = {"acca", "bbbb", "caca"};

    Solution s;
    cout << s.numWays(words, target);
}