#include <vector>
#include <unordered_set>
#include <iostream>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> unique;
        for(int n : nums) {
            if (unique.count(n)) return true;
            unique.insert(n);
        }
        return false;
    }
};

int main() {
    vector<int> nums = {1,2,3,1};
    Solution s;
    cout << s.containsDuplicate(nums);
}