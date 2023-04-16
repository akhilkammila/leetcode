#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};

int main() {
    string s = "heollo";
    string t = "helloo";
    Solution sol;
    cout << sol.isAnagram(s, t);
}