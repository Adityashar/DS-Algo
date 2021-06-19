#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> tree(20001);
vector<vector<int>> up(20001, vector<int>(20));
vector<int> level(20001);

/*
For each NODE we only keep track of ancestors which are at
a level of 0, 1, 2, 4, 8, 16 ... above the CURRENT NODE.

The required KTH LEVEL is written as a binary number.
We recur upwards using the largest bit in our binary number.
O(Log N) to process queries.

*/


void binaryLifting(int u, int p) {
	up[u][0] = p;

	for (int i = 1; i < 20; i++) {
		if (up[u][i - 1] != -1)
			up[u][i] = up[up[u][i - 1]][i - 1];
		else up[u][i] = -1;
	}

	for (auto v : tree[u]) {
		if (v != p) {
			level[v] = level[u] + 1;
			binaryLifting(v, u);
		}
	}
}

int kthAncestor(int u, int level) {
	if (u == -1 || level == 0) return u;

	for (int i = 19; i >= 0; i--) {
		if ((1 << i) <= level) {
			return kthAncestor(up[u][i], level - (1 << i));
		}
	}
	return -1;
}


int LCA(int n1, int n2) {
	// take n1 at the further level
	if (level[n1] < level[n2]) swap(n1, n2);

	for (int i = 19; i >= 0; i--) {
		if (level[n1] - (1 << i) >= level[n2]) {
			n1 = up[n1][i];
		}
	}

	if (n1 == n2) return n1;
	int lca;

	for (int i = 19; i >= 0; i--) {
		if (up[n1][i] != up[n2][i]) {
			n1 = up[n1][i];
			n2 = up[n2][i];
		}
	}

	return up[n1][0];
}


int main() {

	int t;
	cin >> t;

	while (t--) {
		int n;
		cin >> n;

		for (int i = 0; i < n - 1; i++) {
			int x, y;
			cin >> x >> y;
			x--, y--;

			tree[x].push_back(y);
			tree[y].push_back(x);
		}
		level[0] = 0;
		binaryLifting(1, -1);

	}

	return 0;
}