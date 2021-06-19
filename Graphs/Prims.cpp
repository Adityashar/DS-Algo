#include<bits/stdc++.h>
#define pp pair<int, int>
#define pb push_back
#define INF 999999
using namespace std;



int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<pp>> adj(n);

	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		adj[x].pb({y, z});
		adj[y].pb({x, z});
	}

	// define a minHeap

	priority_queue<pp, vector<pp>, greater<pp>> pq;

	// parent to store tree

	vector<int> parent(n, -1);

	// key value to store the min weight edge that connects to the spanning tree

	vector<int> key(n, INF);

	// boolean array telling which nodes have been included in the spanning tree

	vector<bool> mst(n, 0);

	// initial state
	key[0] = 0;
	pq.push({key[0], 0});

	while (pq.size() > 0) {
		pp top = pq.top(); pq.pop();
		int u = top.second;

		// mst inclusion
		mst[u] = 1;

		// iterate over the neighbors and push the nodes which 1. not in the spanning tree 2. show a decrease in their key value
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, w = adj[u][i].second;

			if (mst[v] == 0 && key[v] > w) {
				if (key[v] != INF) pq.erase({key[v], v});
				key[v] = w;
				parent[v] = u;
				pq.push({w, v});
			}

		}

	}

}