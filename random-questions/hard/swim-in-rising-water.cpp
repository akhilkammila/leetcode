#include <vector>
#include <unordered_set>
#include <utility>
#include <iostream>
using namespace std;

// Time complexity: O(n^4)
class Solution {
    vector<int> xChange = {0,0,1,-1};
    vector<int> yChange = {1,-1,0,0};

public:
    // Time complexity of floodfill: O(n^2)
    bool floodFill(vector<vector<int>>& grid, vector<vector<bool>>& visited, int t, int r=0, int c=0) {
        int n = grid.size();
        if (visited[r][c]) return false; //check if already visited
        if (grid[r][c] > t) return false; //check water level
        if (r == n-1 && c == n-1) return true; //base case

        visited[r][c] = true;

        for(int i = 0; i < 4; i++) {
            if(r + yChange[i]< 0 || r + yChange[i]>= n) continue;
            if(c + xChange[i]<0 || c + xChange[i]>=n) continue;

            if (floodFill(grid, visited, t, r+yChange[i], c+xChange[i])) return true;
        }
        return false;
    }

    // Check n^2 different t values
    // We can binary search: only check log(n^2) = log(n) t values
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int l = 0, r = n*n;

        while(l < r) {
            vector<vector<bool>> visited(n, vector<bool>(n, false));
            int t = (l + r)/2;
            if (floodFill(grid, visited, t)) r = t;
            else l = t+1;
        }
        return l;
    }
};

int main() {
    vector<vector<int>> grid = {{0,1,2,3,4},{24,23,22,21,5},{12,13,14,15,16},{11,17,18,19,20},{10,9,8,7,6}};

    Solution sol;
    cout << sol.swimInWater(grid);
}