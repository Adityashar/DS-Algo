#define INF 9999999
#define pp pair<int, int>
#define pd pair<int, double>
#define dp pair<double, int>

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& prob, int start, int end) {
        vector<double> dist(n, INF);
        vector<bool> visited(n, 0);
        vector<vector<pd>> adj(n);
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1];
            double w = prob[i];
            adj[u].push_back({v , w});
            adj[v].push_back({u , w});
        }

        priority_queue<dp> pq;
        pq.push({1.0, start});
        dist[start] = 1;

        while (pq.size() > 0) {
            dp cur = pq.top(); pq.pop();
            double prob_till_now = cur.first;
            int u = cur.second;

            // additional check if the pq top does not contain the "latest" value of max prob from the distance node you
            // can skip this traversal !

            if (prob_till_now != dist[u]) continue;

            for (auto i : adj[u]) {
                double w = i.second;
                int v = i.first;
                if (dist[v] == INF || dist[v] < dist[u] * w) {
                    dist[v] = dist[u] * w;
                    pq.push({dist[v], v});
                }
            }

        }

        return dist[end] == INF ? 0 : dist[end];
    }
};