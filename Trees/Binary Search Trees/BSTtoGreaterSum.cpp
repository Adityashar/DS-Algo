/*

    1038. BST to Greater Sum Tree

// BST
                4
              /   \
            1       6                  Inorder  : 0, 1, 2, 3, 4, 5, 6, 7, 8
          /  \     /  \                Reverse  : 36, 36, 35, 33, 30, 26, 21, 15, 8
         0    2   5    7               Prefix of Inorder
               \        \
                3        8

// Greater Sum Tree

                30
              /   \
            36      21
          /  \     /  \
         36   35  26   15
               \        \
               33        8
*/

// 1

int revInorder(TreeNode* root, int p) {
    if (root == NULL)
        return 0;

    int rightSum = revInorder(root->right, p);
    int leftSum = revInorder(root->left, p + rightSum + root->val);

    root->val = p + root->val + rightSum;

    return root->val - p + leftSum;
}

TreeNode* convertBST(TreeNode* root) {
    if (root == NULL)
        return root;

    revInorder(root, 0);

    return root;
}

// 2

// global variable recursion

int curSum = 0;

void inorder(TreeNode* root) {
    if (root == NULL)
        return ;

    inorder(root->right);
    root->val = curSum += root->val;
    inorder(root->left);
}

// 3

// iterative inorder

TreeNode* bstToGst(TreeNode* root) {
    int curSum = 0;

    if (root == NULL)
        return root;

    TreeNode *cur = root;
    stack<TreeNode*> s;

    while (cur != NULL || s.size() > 0) {
        while (cur != NULL) {
            s.push(cur);
            cur = cur->right;
        }

        cur = s.top(); s.pop();

        cur->val = curSum += cur->val;
        cur = cur->left;
    }

    return root;
}

// 4

// Morris Traversal

TreeNode* bstToGst(TreeNode* root) {
    int curSum = 0;

    if (root == NULL)
        return root;

    TreeNode *cur = root;

    while (cur != NULL) {
        if (cur->left == NULL) {
            cout << cur->val << " ";
            cur = cur->right;
        }
        else {
            // find the predecessor of cur

            TreeNode *pre = cur->left;

            while (pre->right != NULL && pre->right != cur)
                pre = pre->right;

            // Link already exists between the predecessor and cur, predecessor is already included in traversal

            if (pre->right == cur) {
                pre->right = NULL;
                cout << cur->val << " ";
                cur = cur->right;
            }
            else {
                pre->right = cur;
                // cout<<cur->val;  To get the preorder traversal using Morris Method
                cur = cur->left;
            }
        }
    }

    return root;
}