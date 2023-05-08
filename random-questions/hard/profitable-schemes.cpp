#include <vector>
#include <iostream>
using namespace std;

#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#include </Users/akhilkammila/Competitive Programming/debug.h>
#else
#define DEBUG(...) 47;
#endif

/*
State: c crimes considered, m members used, AT LEAST p profit obtained

Overview/Takeaways:
Knapsack dp
When we need to have AT LEAST a certain amount of a single variable, do not 
    increase the size of the dp array
Instead, make the ACTUAL STATE be that "at least" that much of the variable is achieved
*/

class Solution {
public:
    const int mod = 1e9+7;
    int getValue(int c, int m, int p, vector<vector<vector<int>>>& dp) {
        // we are looking for AT LEAST p profit, so transitioning from a state of at least -5
        // is the same as transitioning from a state of at least 0
        if (p < 0) p=0;

        if (c==-1) return (m==0 && p==0); //base case
        if (m < 0) return 0; // cannot have less than 0 members
        return dp[c][m][p] % mod;
    }

    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        // c x m x p vector
        vector<vector<vector<int>>> dp(group.size(), vector<vector<int>>(n+1, vector<int>(minProfit+1)));

        for(int c = 0; c < group.size(); c++) {
            for(int p = 0; p <= minProfit; p++) {
                for(int m = 0; m <= n; m++) {
                    // two cases: use this crime, dont use this crime
                    dp[c][m][p] = (getValue(c-1, m, p, dp) + getValue(c-1, m-group[c], p-profit[c], dp)) % mod;
                }
            }
        }

        // we sum the states where all crimes are considered and minprofit is at least minprofit,
        // for all member counts
        int answ = 0;
        for(int m = 0; m <= n; m++) {
            answ += getValue(group.size()-1, m, minProfit, dp);
            answ %= mod;
        }
        return answ;
    }
};

int main() {
    Solution s = Solution();
    
    int n = 5;
    int minProfit= 3;
    vector<int> group = {2,2};
    vector<int> profit = {2,3};
    cout << s.profitableSchemes(n, minProfit, group, profit);
}