#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> tree(20001);

/* method one

You keep a count of the number of keys you have encountered while
traversing using DFS throughout the tree .
Get the count of matchingNodes in lefttree and righttree.
Add 1 to it if root is also a key.

if size of keys == matchingNodes, add this node to list of ancestors

return this value for further recursion to happen.

*/

int getKeysCount(int root, vector<int> &keys, vector<int> &ancestors, int matchingNodes) {

	for (auto v : tree[root]) {
		matchingNodes += getKeysCount(v, keys, ancestors, matchingNodes);
	}

	if (find(keys.begin(), keys.end(), root) != keys.end())
		matchingNodes++;

	if (matchingNodes == keys.size())
		ancestors.push_back(root);

	return matchingNodes;
}


int getLCA(int root, vector<int> &keys) {

	vector<int> ancestors;

	int matchingNodes = 0;
	getKeysCount(root, keys, ancestors, matchingNodes);

	return ancestors[0];
}

/*
Method 2

Maintain the intimes and the outtimes of each node

For a node to be the ancestor of K Nodes -
1. its intime should be lower or equal to each of theirs
2. its outtime should be higher or equal to each of theirs

*/

vector<int> intimes(20001);
vector<int> outtimes(20001);
vector<int> level(20001);
int time = 0;

void DFS(int root, int parent) {
	time++;
	intimes[root] = time;

	if (parent == -1) level[root] = 0;
	else level[root] = level[parent] + 1;

	for (auto v : tree[root]) {
		if (v != parent) {
			DFS(v, u);
		}
	}

	time++;
	outtimes[root] = time;
}


int getLCA(vector<int> &keys) {

	int minInTime = INT_MAX, maxOutTime = INT_MIN;
	int minNode, maxNode;

	for (auto i : keys) {
		if (minInTime > intimes[i]) {
			minInTime = intimes[i];
			minNode = i;
		}
		if (maxOutTime < outtimes[i]) {
			maxOutTime = outtimes[i];
			maxNode = i;
		}
	}

	if (minNode == maxNode)
		return minNode;

	int minLevel = min(level[maxNode], level[minNode]);
	int node, l = -2;

	for (auto u : tree) {
		if (level[u] > minLevel)
			continue;

		if (intimes[u] <= minInTime && outtimes[u] >= maxOutTime && level[u] < l) {
			l = level[node];
			node = u;
		}
	}

	return node
	       ;
}


int main() {
	int t = 1;

	while (t--) {
		int n;
		cin >> n;

		for (int i = 0; i < n - 1; i++) {
			int x, y;
			cin >> x >> y;
			tree[x].push_back(y);
			tree[y].push_back(x);
		}

		vector<int> keys = {};

		DFS(0, -1);

		cout << getLCA(0, keys);

	}

	return 0;
}