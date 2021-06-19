#include<bits/stdc++.h>
#define pp pair<int, int>
#define pb push_back
#define INF 999999
using namespace std;

vector<bool> set, stack, cycle;

bool dfs(vector<vector<int>>& adj, int index) {
	if (set[index] == 0) {
		set[index] = 1;
		stack[index] = 1;

		for (int i = 0; i < adj[index].size(); i++) {
			int v = adj[index][i];

			if (set[v] == 0 && dfs(adj, v)) {
				cycle[v] = 1;
				return true;
			}
			else if (stack[v] == 1) {
				// back edge
				cycle[v] = 1;
				return true;
			}

		}
	}

	stack[index] = 0;
	return false;
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
	vector<int> nodes;
	int n = graph.size();
	stack.resize(n, 0);
	cycle.resize(n, 0);
	set.resize(n, 0);

	for (int i = 0; i < n; i++) {
		if (set[i] == 0 && dfs(graph, i)) {
			cycle[i] = 1;
		}
	}

	for (int i = 0; i < n; i++) if (!cycle[i]) nodes.push_back(i);

	return nodes;
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n);

	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y;
		adj[x].pb(y);
	}

	vector<int> ans = eventualSafeNodes(adj);
	for (auto i : ans) cout << i << " ";

	return 0;
}