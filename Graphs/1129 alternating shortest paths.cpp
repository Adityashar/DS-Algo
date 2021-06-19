#define pp pair<int, int>
#define ppp pair<int, pp>
#define INF 9999999
class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red, vector<vector<int>>& blue) {
        vector<vector<pp>> adj(n);

        for (int i = 0; i < red.size(); i++) {
            int x = red[i][0], y = red[i][1];
            adj[x].push_back({y, 1});
        }
        for (int i = 0; i < blue.size(); i++) {
            int x = blue[i][0], y = blue[i][1];
            adj[x].push_back({y, 0});
        }

        priority_queue<ppp, vector<ppp>, greater<ppp>> pq;

        vector<int> dist(n, INF);

        dist[0] = 0;
        pq.push({0, {0, -1}});

        while (pq.size() > 0) {
            ppp cur = pq.top(); pq.pop();
            int u = cur.second.first, d = cur.first;

            int color_prev_edge = cur.second.second;

            for (int i = 0; i < adj[u].size(); i++) {
                int color_next_edge = adj[u][i].second, neigh = adj[u][i].first;

                if (color_prev_edge == -1 || color_next_edge == 1 - color_prev_edge) {

                    if (dist[neigh] > d + 1) {
                        dist[neigh] = d + 1;
                    }

                    pq.push({d + 1, {neigh, color_next_edge}});
                }
            }
            int cnt = n;
            for (auto i : dist) if (i != INF) cnt--;
            if (cnt == 0) break;

        }
        for (int i = 0; i < n; i++) if (dist[i] == INF) dist[i] = -1;
        return dist;
    }
};


// BFS

#define pp pair<int, int>
#define ppp pair<int, pp>
#define INF 9999999
class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red, vector<vector<int>>& blue) {
        vector<vector<pp>> adj(n);
        vector<vector<int>> dp(n, vector<int>(2, INF));

        for (int i = 0; i < red.size(); i++) {
            int x = red[i][0], y = red[i][1];
            adj[x].push_back({y, 1});
        }
        for (int i = 0; i < blue.size(); i++) {
            int x = blue[i][0], y = blue[i][1];
            adj[x].push_back({y, 0});
        }

        queue<pp> q;
        vector<int> dist(n, INF);
        q.push({0, 1});
        q.push({0, 0});
        int level = 0;

        while (q.size() > 0) {
            int s = q.size();
            while (s--) {
                pp cur = q.front(); q.pop();
                int u = cur.first, color_prev = cur.second;

                dp[u][color_prev] = level;

                for (auto i : adj[u]) {
                    int v = i.first, color_next = i.second;
                    if (color_next == 1 - color_prev) {
                        if (dp[v][color_next] == INF) {
                            dp[v][color_next] = dp[u][color_prev] + 1;
                            q.push({v, color_next});
                        }
                    }
                }
            }
            if (q.size() == 0) break;
            level++;
        }


        for (int i = 0; i < n; i++) dist[i] = (dp[i][0] == INF && dp[i][1] == INF) ? -1 : min(dp[i][0], dp[i][1]);
        return dist;
    }
};