/*

Diameter is the distance between the farthest two leaves of a tree
Longest path between two nodes in a tree

*/

// 1

// For N-Ary tree with Adjacency List

#define pp pair<int, int>
#define f first
#define s second

vector<vector<int>> adj;

pp DFS(int root, int parent) {

	int ans = 0, target = root;

	for (auto u : adj[root]) {
		if (u == parent)
			continue;

		pp child = DFS(u, root);

		if (child.f > ans)
			ans = child.f, target = chilf.s;

	}

	return { ans + 1, target };
}

int Diameter(int root) {

	// find the farthest leaf node
	pp F = DFS(root, -1);

	// use the farthest leaf as the root to find the farthest leaf again
	pp S = DFS(F.s, -1);

	return S.f;
}


// 2

// For Binary Tree

int getDiameter(TreeNode* root) {
	if (root == NULL) return 0;

	int leftPathLeaf = getDiameter(root->left);
	int rightPathLeaf = getDiameter(root->right);

	ans = max(ans, leftPathLeaf + rightPathLeaf + 1);

	return 1 + max(leftPathLeaf, rightPathLeaf);
}