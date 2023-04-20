#include <vector>
#include <iostream>
#include <queue>
using namespace std;

#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#include </Users/akhilkammila/Competitive Programming/debug.h>
#else
#define DEBUG(...) 47;
#endif

class Solution {
public:
    void bfs(int n, int p, vector<bool>& banned, int k, vector<int>& distances) {
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
                for(int j = l; j <= r; j += 2) {
                    if (distances[j] != -1 || banned[j]) continue;
                    q.push(j);
                }
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