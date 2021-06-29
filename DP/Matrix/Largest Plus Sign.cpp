/*
    764. Largest Plus Sign

    1 1 1 1
    0 1 0 1
    1 1 1 1
    1 1 0 1

    MaxSize = 2
*/

class Solution {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {

        vector<vector<int>> dp(n, vector<int>(n, n + 1));

        for (auto &m : mines)
            dp[m[0]][m[1]] = 0;

        for (int i = 0; i < n; i++) {

            // Left To Right maximum successive ones for each row

            for (int j = 0, l = 0; j < n; j++) {
                l = dp[i][j] == 0 ? 0 : l + 1;
                dp[i][j] = min(dp[i][j], l);
            }

            // Right To Left maximum successive ones for each row

            for (int j = n - 1, r = 0; j >= 0; j--) {
                r = dp[i][j] == 0 ? 0 : r + 1;
                dp[i][j] = min(dp[i][j], r);
            }

            // Top to Down maximum successive ones for each column

            for (int j = 0, d = 0; j < n; j++) {
                d = dp[j][i] == 0 ? 0 : d + 1;
                dp[j][i] = min(dp[j][i], d);
            }

            // Down To Top maximum successive ones for each column

            for (int j = n - 1, u = 0; j >= 0; j--) {
                u = dp[j][i] == 0 ? 0 : u + 1;
                dp[j][i] = min(dp[j][i], u);
            }
        }

        int ans = 0;

        for (auto i : dp)
            for (auto j : i)
                ans = max(j, ans);

        return ans;
    }
};