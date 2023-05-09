#include <iostream>
#include <vector>
using namespace std;

#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#include </Users/akhilkammila/Competitive Programming/debug.h>
#else
#define DEBUG(...) 47;
#endif

/*
Should have used priority queue for optimal soln
This simple O(n^2) still passes bc it is an easy prob
*/

class Solution {
public:
    // returns whether we smashed stones together: -2 if smashed, else the weight remaining
    int smashStones(vector<int>& stones) {
        int heaviest = 0; int hIndex = -1;
        int nextHeaviest = 0; int nIndex = -1;

        for(int i = 0; i < stones.size(); i++) {
            int weight = stones[i];

            if (weight > heaviest) {
                nextHeaviest = heaviest; nIndex = hIndex;
                heaviest = weight; hIndex = i;
            }
            else if (weight > nextHeaviest) {
                nextHeaviest = weight; nIndex = i;
            }
        }

        if (nextHeaviest == 0) return heaviest;
        stones[hIndex] -= nextHeaviest;
        stones[nIndex] = 0;
        return -2;
    }

    int lastStoneWeight(vector<int>& stones) {
        int last = -2;
        while(last == -2) {
            last = smashStones(stones);
        }
        return last;
    }
};

int main() {
    Solution s = Solution();
    vector<int> stones = {2,7,4,1,8,1};
    cout << s.lastStoneWeight(stones);
}