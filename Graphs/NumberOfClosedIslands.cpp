// DFS 1



// UNION & FIND


// DFS 2

class Solution {
public:
	vector<vector<bool>> v;
	vector<int> x, y;
	int n, m;

	void DFS(vector<vector<int>> &grid, int r, int c) {
		v[r][c] = 1;
		for (int i = 0; i < 4; i++) {
			int xn = r + x[i], yn = c + y[i];
			if (xn >= 0 && yn >= 0 && yn < m && xn < n && !v[xn][yn] && grid[xn][yn] == 0)
				DFS(grid, xn, yn);
		}
	}

	int closedIsland(vector<vector<int>>& grid) {
		n = grid.size(), m = grid[0].size();
		x = {1, -1, 0, 0}, y = {0, 0, 1, -1};
		int cnt = 0;
		v.resize(n, vector<bool>(m, 0));

		for (int i = 0; i < n; i++) {
			if (!v[i][0] && grid[i][0] == 0)
				DFS(grid, i, 0);
			if (!v[i][m - 1] && grid[i][m - 1] == 0)
				DFS(grid, i, m - 1);
		}

		for (int i = 0; i < m; i++) {
			if (!v[0][i] && grid[0][i] == 0)
				DFS(grid, 0, i);
			if (!v[n - 1][i] && grid[n - 1][i] == 0)
				DFS(grid, n - 1, i);
		}

		for (int i = 1; i < n - 1; i++) {
			for (int j = 1; j < m - 1; j++) {
				if (!v[i][j] && grid[i][j] == 0) {
					DFS(grid, i, j);
					cnt++;
				}
			}
		}

		return cnt;
	}
};