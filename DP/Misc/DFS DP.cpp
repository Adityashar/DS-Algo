/*

    1. Longest Increasing Path in Matrix
    Given an m x n integers matrix, return the length of the longest increasing path in matrix.

*/

class Solution {
public:
    vector<vector<int>> dp;
    vector<vector<bool>> visited;

    int DFS(vector<vector<int>>& matrix, int r, int c, int cur) {
        int n = matrix.size();
        int m = matrix[0].size();

        if (dp[r][c] != -1)
            return dp[r][c];

        int ans = 0;
        int x[] = {1, -1, 0, 0}, y[] = {0, 0, 1, -1};

        visited[r][c] = 1;

        for (int i = 0; i < 4; i++) {
            int xn = x[i] + r, yn = y[i] + c;

            if (xn >= 0 && yn >= 0 && yn < m && xn < n && !visited[xn][yn] && (cur < matrix[xn][yn])) {
                ans = max(ans, DFS(matrix, xn, yn, matrix[xn][yn]));
            }
        }

        visited[r][c] = 0;
        return dp[r][c] = ans + 1;
    }

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        dp.resize(n, vector<int>(m, -1));
        visited.resize(n, vector<bool>(m, 0));

        int ans = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                DFS(matrix, i, j, matrix[i][j]);
                ans = max(dp[i][j], ans);
            }
        }

        return ans;
    }
};