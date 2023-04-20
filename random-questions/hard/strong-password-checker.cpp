/*
https://leetcode.com/problems/strong-password-checker/

Greedy problem solving problem, O(n)
Idea: only use add if length <6, only use delete if length > 20
see how many replaces we need, and see how much delete reduces our replace count
*/

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

class Solution {
public:
    // Returns a number 1-3 for how much of (1) lowercase (2) uppercase (3) digit we have left to add
    int conditionsLeft (string password) {
        bool lowercase = false, uppercase = false, digit = false;
        for(char c : password) {
            if (islower(c)) lowercase = true;
            if (isupper(c)) uppercase = true;
            if (isdigit(c)) digit = true;
        }
        return 3 - (lowercase + uppercase + digit);
    }

    // Find the length of all sequences
    vector<int> findSequences (string password) {
        vector<int> sequences = {};

        int seqLength = 1;
        for(int i = 1; i < password.size(); i++) {
            if (password[i] == password[i-1]) seqLength++;
            else {
                if (seqLength >= 3) sequences.push_back(seqLength);
                seqLength = 1;
            }
        }
        if (seqLength >= 3) sequences.push_back(seqLength);
        return sequences;
    }

    // Find moves to work with replace
    int movesWithReplace(int length) {
        return length/3;
    }

    // Reduce vector
    vector<int> deleteFromVector(vector<int>& seq) {
        int oneCost=0, twoCost=0, threeCost=0;
        for(int i = 0; i < seq.size(); i++) {
            if (seq[i]%3 == 0) {
                oneCost ++;
                threeCost += (seq[i]-1-2)/3;
            }
            if (seq[i]%3 == 1) {
                twoCost++;
                threeCost += (seq[i]-2-2)/3;
            }
            if (seq[i]%3 == 2) {
                threeCost += (seq[i]-2)/3;
            }
        }
        vector<int> res = {oneCost, twoCost, threeCost};
        return res;
    }

    int strongPasswordChecker(string password) {
        // takes care of all ADD operations
        if (password.size() < 6) return max(6 - (int)password.size(), conditionsLeft(password));
        
        // takes care of all 6-20 length strings
        if (password.size() <= 20) {
            vector<int> sequences = findSequences(password);
            int total = 0;
            for(int i : sequences) {
                total += movesWithReplace(i);
            }
            return max(total, conditionsLeft(password));
        }
        
        // all 21+ length strings
        vector<int> sequences = findSequences(password);
        int total = 0;
        for(int i : sequences) {
            total += movesWithReplace(i);
        }

        int toDelete = password.size() - 20;
        vector<int> costs = deleteFromVector(sequences);
        // cout << costs[0] << ' ' << costs[1] << ' ' << costs[2] << endl;
        int saved = 0;
        for(int i = 0; i < 3; i++) {
            costs[i] = min(costs[i], toDelete/(i+1));
            saved += costs[i];
            toDelete -= (i+1)*costs[i];
        }
        // cout << total << ' ' << saved << ' ' << password.size() - 20 << endl;
        return (password.size() - 20) + max(total - saved, conditionsLeft(password));
    }
};

int main() {
    string password = "!!!!1.....aaaabbbbbiasdjfoas";
    Solution s;
    cout << s.strongPasswordChecker(password);
}