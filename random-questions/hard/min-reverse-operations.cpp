/*
https://leetcode.com/problems/minimum-reverse-operations/description/
This problem is pretty hard
Uses an uncommon idea: we have a graph of size n^2, but after we visit a node, we never go back to it
Because of how the problem is set up, if we can split up the unvisited vertices by their parity. Then,
the vertices that a vertex will go to are all contiguous

Could make leetcode post on this in the future
*/

#include <vector>
#include <iostream>
#include <queue>
#include <set>
using namespace std;

#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#include </Users/akhilkammila/Competitive Programming/debug.h>
#else
#define DEBUG(...) 47;
#endif

class Solution {
public:
    void addNeighbors(queue<int>& q, set<int>& neighbors, int l, int r) {
        set<int>::iterator begin_it = neighbors.lower_bound(l);
        set<int>::iterator end_it = neighbors.upper_bound(r);
        while(begin_it != end_it) {
            int val = *begin_it;
            q.push(val);
            begin_it = neighbors.erase(begin_it);
        }
    }

    void bfs(int n, int p, vector<bool>& banned, int k, vector<int>& distances) {
        // Keep track of visited and unvisited nodes
        set<int> odds, evens;
        for(int i = 0; i < n; i++) {
            if (banned[i]) continue;
            if (i%2 == 0) evens.insert(i);
            else odds.insert(i);
        }

        // Initialize queue
        queue<int> q;
        q.push(p);
        int j = k-1;

        int dist = 0;
        while(q.size()) {
            int s = q.size();

            for(int i = 0; i < s; i++) {
                // Find the index that we visited, make sure that it is unvisited (new best!)
                int index = q.front();
                q.pop();
                if (distances[index] != -1 || banned[index]) continue;

                distances[index] = dist; // mark its distance

                // Add neighbors
                int l = abs(index - j);
                int r = min(index + j, 2*n - j - index - 2);
                
                // Add neighbors by looking at the set of possible neighbors
                // in the range [l, r]
                if (l%2 == 0) addNeighbors(q, evens, l, r);
                else addNeighbors(q, odds, l, r);
            }
            dist++;
        }
    }
    
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        // initialize distances array
        vector<int> distances(n, -1);

        // make new banned array for lookups
        vector<bool> newBanned(n, false);
        for(int i : banned) newBanned[i] = true;

        // bfs starting from root
        bfs(n, p, newBanned, k, distances);
        return distances;
    }
};

int main() {
    int n = 10;
    int p = 0;
    vector<int> banned = {};
    int k = 4;

    Solution s;
    s.minReverseOperations(n, p, banned, k);
}