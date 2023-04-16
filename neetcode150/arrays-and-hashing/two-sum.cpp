#include <vector>
#include <iostream>
#include <unordered_map>
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
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> unique;
        for(int i = 0; i < nums.size(); i++) {
            if (nums[i]*2 == target) {
                if (unique.count(nums[i])) return {unique[nums[i]], i};
            }
            unique[nums[i]]=i;
        }
        for(int i = 0; i < nums.size(); i++) {
            if (nums[i]*2 == target) continue;
            if (unique.count(target - nums[i])) {
                return {i, unique[target-nums[i]]};
            }
        }
        return {};
    }
};

int main() {
    vector<int> nums = {3,2,3};
    int target = 6;

    Solution s;
    vector<int> answ = s.twoSum(nums, target);
    DEBUG(answ);
}