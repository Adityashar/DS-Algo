class Solution {
public:
    vector<bool> visited;
    int d, N;
    double maxAns;
    vector<int> path;
    void dfs(int s, vector<vector<int>>& edges, vector<double>& prob, double p) {
        if (s == d) {
            maxAns = max(maxAns, p);
            // for(auto i: path) cout<<i<<" ";
            // cout<<endl;
            return;
        }
        visited[s] = true;
        // path.push_back(s);

        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1];
            double w = prob[i];
            if (u == s && !visited[v]) {
                dfs(v, edges, prob, p * w);
            }
            else if (v == s && !visited[u]) {
                dfs(u, edges, prob, p * w);
            }
        }

        // path.pop_back();
        visited[s] = false;
        return ;
    }

    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        double ans = 1;
        visited.resize(n, 0);
        d = end, N = n, maxAns = 0;
        dfs(start, edges, succProb, ans);

        return maxAns;
    }
};