# Basics Of Binary Trees

## 1. Complete Binary Tree

Given the root of a binary tree, determine if it is a complete binary tree.

In a complete binary tree, every level, except possibly the last, is completely filled,
and all nodes in the last level are as far left as possible.
It can have between 1 and 2h nodes inclusive at the last level h.

Input: root = [1, 2, 3, 4, 5, 6]
              Output: true
              Explanation:

  Every level before the last is full (ie. levels with node - values {1} and {2, 3}),
  and all nodes in the last level ({4, 5, 6}) are as far left as possible.

#### Approach
  The first null encountered in the BFS traversal of a complete BT is after all the nodes in the tree are traversed
  and no other nodes are left.

```cpp

    bool isCompleteTree(TreeNode* root) {
    if (root == NULL)
        return true;

    queue<TreeNode*> q;
    q.push(root);
    bool null = false;

    while (q.size() > 0) {
        TreeNode *cur = q.front();
        q.pop();

        if (cur == NULL)
            null = true;
        else {
            if (null)
                return false;

            q.push(cur->left);
            q.push(cur->right);
        }
    }

    return true;
}



bool isCompleteTree(TreeNode* root) {
    if (root == NULL)
        return true;

    queue<pp> q;
    q.push({root, 0});
    int level = 0, start = -1;

    while (q.size() > 0) {
        int s = q.size();
        int cnt = 0, prev = start;

        while (s--) {
            pp cur = q.front();
            q.pop();
            int index = cur.s;
            cnt++;

            if (index != prev + 1) {
                return false;
            }

            prev = index;

            if (cur.f->left)
                q.push({cur.f->left, index * 2 + 1});
            if (cur.f->right)
                q.push({cur.f->right, index * 2 + 2});
        }

        long need = pow(2, level);
        start += need;

        if (need != cnt && q.size() > 0) {
            return false;
        }
        level++;
    }

    return true;
}
```


## 2. Check Mirror N-Ary Trees

https://www.geeksforgeeks.org/check-mirror-n-ary-tree/

hashmap: node-> stack of children

iterate over edges of other tree
top of stack[cur]  should be v
if not return false
              else pop


## 3. Symmetry

Each level is a palindrome.


```cpp

// C++ program to check if a given Binary
// Tree is symmetric or not

                  bool isSymmetric(struct Node* root)
    {
        if (root == NULL)
            return true;

        // If it is a single tree node, then
        // it is a symmetric tree.
        if (!root->left && !root->right)
            return true;

        queue <Node*> q;

        // Add root to queue two times so that
        // it can be checked if either one child
        // alone is NULL or not.
        q.push(root);
        q.push(root);

        // To store two nodes for checking their
        // symmetry.
        Node* leftNode, *rightNode;

        while (!q.empty()) {

            // Remove first two nodes to check
            // their symmetry.
            leftNode = q.front();
            q.pop();

            rightNode = q.front();
            q.pop();

            // if both left and right nodes
            // exist, but have different
            // values--> inequality, return false
            if (leftNode->key != rightNode->key) {
                return false;
            }

            // Push left child of left subtree node
            // and right child of right subtree
            // node in queue.
            if (leftNode->left && rightNode->right) {
                q.push(leftNode->left);
                q.push(rightNode->right);
            }

            // If only one child is present alone
            // and other is NULL, then tree
            // is not symmetric.
            else if (leftNode->left || rightNode->right)
                return false;

            // Push right child of left subtree node
            // and left child of right subtree node
            // in queue.
            if (leftNode->right && rightNode->left) {
                q.push(leftNode->right);
                q.push(rightNode->left);
            }

            // If only one child is present alone
            // and other is NULL, then tree
            // is not symmetric.
            else if (leftNode->right || rightNode->left)
                return false;
        }

        return true;
    }

```