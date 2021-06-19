#define INF 9999999
#define pp pair<int, int>

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int s, int d, int stops) {
        vector<vector<int>> dp(n, vector<int>(stops + 1, INF));
        dp[s][0] = 0;

        vector<vector<int>> adj(n, vector<int>(n, INF));
        for (auto f : flights) adj[f[0]][f[1]] = f[2];

        for (int k = 0; k <= stops; k++) {
            for (int i = 0; i < n; i++) {
                if (k == 0) dp[i][k] = adj[s][i];
                else {
                    for (int j = 0; j < n; j++) {
                        if (adj[j][i] != INF)
                            dp[i][k] = min(dp[i][k], adj[j][i] + dp[j][k - 1]);
                    }
                }
            }
            for (auto f : flights) {
                int u = f[0], v = f[1], w = f[2];
                if (k == 0 && u == s) dp[v][0] = w;
                else {
                    dp[v][k] = min(dp[v][k], w + dp[u][k - 1])
                }
            }
        }

        int minans = INF;
        for (int i : dp[d]) minans = min(minans, i);

        return minans == INF ? -1 : minans;
    }
};