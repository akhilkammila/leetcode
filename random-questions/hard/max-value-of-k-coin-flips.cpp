#include <vector>
#include <iostream>
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
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        // Make piles --> prefix piles
        for(int i = 0; i < piles.size(); i++) {
            for(int j = 1; j < piles[i].size(); j++) {
                piles[i][j] += piles[i][j-1];
            }
        }

        // Make dp array
        vector<vector<int>> dp(piles.size()+1, vector<int>(k+1, 0));

        // Dp recurrence
        for(int p = 1; p < piles.size()+1; p++) {
            for(int c = 1; c <= k; c++) {
                int val = dp[p-1][c];
                for(int i = 1; i <= min(c, (int)piles[p-1].size()); i++) { //adding in current pile
                    int curr = piles[p-1][i-1];
                    curr += dp[p-1][c-i];
                    val = max(val, curr);
                }
                dp[p][c] = val;
            }
        }
        return dp[piles.size()][k];
    }
};

int main() {
    vector<vector<int>> piles = {{1,100,3},{7,8,9}};
    int k = 2;

    Solution s;
    cout << s.maxValueOfCoins(piles, k);
}