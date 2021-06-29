#include<bits/stdc++.h>
using namespace std;

queue<TreeNode*> q;

bool burnTree(TreeNode* root, int target) {
	if (root == NULL)
		return false;

	if (root->val == target) {
		cout << target << endl;

		if (root->left)
			q.push(root->left);
		if (root->right)
			q.push(root->right);

		return true;
	}

	bool left = burnTree(root->left, target);

	if (left) {
		int s = q.size();

		while (s--) {
			TreeNode *cur = q.front();
			cout << cur->val << " ";

			if (root->left)
				q.push(root->left);
			if (root->right)
				q.push(root->right);
		}

		cout << root->val << endl;
		if (root->right)
			q.push(root->right);

		return true;
	}

	bool right = burnTree(root->right, target);

	if (right) {
		int s = q.size();

		while (s--) {
			TreeNode *cur = q.front();
			cout << cur->val << " ";

			if (root->left)
				q.push(root->left);
			if (root->right)
				q.push(root->right);
		}

		cout << root->val << endl;
		if (root->left)
			q.push(root->left);

		return true;
	}

	return 0;
}

int main() {

	while (q.size() > 0) {
		int s = q.size();

		while (s--) {
			TreeNode *cur = q.front();
			cout << cur->val << " ";

			if (root->left)
				q.push(root->left);
			if (root->right)
				q.push(root->right);
		}
		cout << endl;
	}

	return 0;
}
