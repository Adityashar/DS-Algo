#include<bits/stdc++.h>
using namespace std;

int n, m;

int longestLine(vector<vector<int>> &M) {
	n = M.size();
	m = M[0].size();

	vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(4, 0)));

	int x[] = { -1, 0, -1, -1};
	int y[] = {0, -1, -1, 1};
	int ans = 0;

	for (int i = 0; i < n; i++) {
		for (int k = 0; k < 4; k++) {
			if (k == 0 && i != 0) {

				dp[i][0][k] = M[i][0] == 0 ? 0 : 1 + dp[i - 1][0][k];
			}
			else dp[i][0][k] = M[i][0];
			if (k == 3)
				dp[i][m - 1][k] = M[i][0];
			ans = max(ans, dp[i][0][k]);
		}
	}

	for (int i = 0; i < m; i++) {
		for (int k = 0; k < 4; k++) {
			if (k == 1 && i != 0) {
				dp[0][i][k] = M[0][i] == 0 ? 0 : 1 + dp[0][i - 1][k];
			}
			else dp[0][i][k] = M[0][i];

			ans = max(ans, dp[0][i][k]);
		}
	}


	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m ; j++) {
			for (int k = 0; k < 4; k++) {
				if (k == 3 && j == m - 1)
					continue;
				int xn = i + x[k], yn = j + y[k];
				dp[i][j][k] = M[i][j] == 0 ? 0 : 1 + dp[xn][yn][k];
				ans = max(dp[i][j][k], ans);
			}
		}
	}

	// for (int k = 0; k < 4; k++) {
	// 	for (int i = 0; i < n; i++) {
	// 		for (int j = 0; j < m; j++) {
	// 			cout << dp[i][j][k] << " ";
	// 		}
	// 		cout << endl;
	// 	}
	// 	cout << endl;
	// }

	return ans;
}


int main() {

	vector<vector<int>> M = {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 1}};
	cout << longestLine(M);

	return -1;
}