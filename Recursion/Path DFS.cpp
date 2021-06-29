/*

1. Rat in a Maze

Consider a rat placed at (0, 0) in a square matrix of order N * N. It has to reach the destination at (N - 1, N - 1).
Find all possible paths that the rat can take to reach from source to destination.
The directions in which the rat can move are 'U'(up), 'D'(down), 'L' (left), 'R' (right).
Value 0 at a cell in the matrix represents that it is blocked and rat cannot move to it.
Value 1 at a cell in the matrix represents that rat can be travel through it.

*/


class Solution {
public:
    vector<string> ans;
    vector<vector<bool>> visited;

    void DFS(vector<vector<int>> &m, string &t, int r, int c) {
        int n = m.size();

        if (r == n - 1 && c == n - 1) {
            ans.push_back(t);
            return;
        }

        visited[r][c] = 1;

        int x[] = {1, -1, 0, 0}, y[] = {0, 0, 1, -1};
        char dir[] = {'D', 'U', 'R', 'L'};

        for (int i = 0; i < 4; i++) {
            int xn = x[i] + r, yn = y[i] + c;
            if (xn >= 0 && yn >= 0 && xn < n && yn < n && !visited[xn][yn] && m[xn][yn] != 0) {
                t += dir[i];
                DFS(m, t, xn, yn);
                t.pop_back();
            }
        }

        visited[r][c] = 0;
    }

    vector<string> findPath(vector<vector<int>> &m, int n) {
        if (m[0][0] == 0 || m[n - 1][n - 1] == 0)
            return ans;

        string temp = "";
        visited.resize(n, vector<bool>(n, 0));

        DFS(m, temp, 0, 0);

        sort(ans.begin(), ans.end());

        return ans;
    }
};

/*

    2. Unique Paths III

    On a 2-dimensional grid, there are 4 types of squares:

    1 represents the starting square.  There is exactly one starting square.
    2 represents the ending square.  There is exactly one ending square.
    0 represents empty squares we can walk over.
    -1 represents obstacles that we cannot walk over.
    Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.

*/


class Solution {
public:
    int ei, ej, n, m, count;
    vector<vector<int>> dp;
    vector<vector<bool>> v;

    int DFS(vector<vector<int>>& grid, int r, int c, int steps) {
        if (grid[r][c] == 2 && steps == 0) {
            count++;
            return dp[r][c] = 1;
        }

        if (grid[r][c] == 2)
            return 0;

        // if(dp[r][c] != -1)
        //     return dp[r][c];

        v[r][c] = 1;

        int ans = 0;
        int x[] = {1, -1, 0, 0}, y[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++) {
            int xnew = r + x[i], ynew = c + y[i];

            if (xnew >= 0 && ynew >= 0 && xnew < n && ynew < m && grid[xnew][ynew] != -1 && !v[xnew][ynew]) {
                ans += DFS(grid, xnew, ynew, steps - 1);
            }
        }

        v[r][c] = 0;

        return dp[r][c] = ans;
    }

    int uniquePathsIII(vector<vector<int>>& grid) {
        int si, sj, steps = 0;

        n = grid.size(), m = grid[0].size();
        count = 0;
        dp.resize(n, vector<int>(m, -1));
        v.resize(n, vector<bool>(m, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1)
                    si = i, sj = j;
                if (grid[i][j] == 2)
                    ei = i, ej = j;
                if (grid[i][j] != -1)
                    steps++;
            }
        }

        int ans = DFS(grid, si, sj, steps - 1);

        return count;
    }
};

/*

    4. Path with Maximum Gold

    In a gold mine grid of size m x n,
    each cell in this mine has an integer representing the amount of gold in that cell, 0 if it is empty.

    Return the maximum amount of gold you can collect under the conditions:

    Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
    Output: 24

    Explanation:
    [[0,6,0],
     [5,8,7],
     [0,9,0]]

    Path to get the maximum gold, 9 -> 8 -> 7.

*/

class Solution {
public:
    vector<vector<bool>> v;
    int n, m;

    int DFS(vector<vector<int>>& grid, int i, int j) {

        v[i][j] = 1;
        int ans = 0;
        int x[] = {1, -1, 0, 0}, y[] = {0, 0, -1, 1};

        for (int k = 0; k < 4; k++) {
            int xn = i + x[k], yn = j + y[k];
            if (xn >= 0 && yn >= 0 && xn < n && yn < m && !v[xn][yn] && grid[xn][yn] != 0)
                ans = max(ans, DFS(grid, xn, yn));
        }

        v[i][j] = 0;

        return ans + grid[i][j];
    }

    int getMaximumGold(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();
        v.resize(n, vector<bool>(m, 0));

        int ans = -1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] != 0) {
                    int val = DFS(grid, i, j);
                    ans = max(ans, val);
                }
            }
        }

        return ans;
    }
};