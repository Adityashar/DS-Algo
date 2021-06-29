/*

    1373. Maximum Sum BST in Binary Tree

    Given a binary tree root, the task is to return the maximum sum of all keys of any sub-tree which is also a Binary Search Tree (BST).

    Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
    Output: 20
    Explanation: Maximum sum in a valid Binary search tree is obtained in root node with key equal to 3.

*/
class Solution {
public:

    int maxNode(TreeNode *root) {
        while (root->right != NULL)
            root = root->right;

        return root->val;
    }

    int minNode(TreeNode *root) {
        while (root->left != NULL)
            root = root->left;

        return root->val;
    }

    vector<int> DFS(TreeNode *root) {
        if (root == NULL) {
            return {0, 1, 0, INT_MIN, INT_MAX};
        }

        if (root->right == NULL && root->left == NULL)
            return {root->val, 1, root->val, root->val, root->val};

        vector<int> left = DFS(root->left);
        vector<int> right = DFS(root->right);

        vector<int> ans(5);

        bool f1 = true, f2 = true;

        if (root->left)
            f1 = left[1] && root->val > left[3];//maxNode(root->left);

        if (root->right)
            f2 = right[1] && root->val < right[4];//minNode(root->right);


        // check given root's tree is BST or not;

        ans[1] = f1 && f2;

        // if BST, then find the sum of this tree, else 0;

        ans[2] = ans[1] ? left[2] + right[2] + root->val : 0;

        // max sum of the current BSTs

        ans[0] = max({ ans[2], left[0], right[0] });

        // set the max

        ans[3] = max({ root->val, left[3], right[3] });

        // set the min

        ans[4] = min({ root->val, left[4], right[4] });

        // if(ans[1]) {
        //     for(auto i: ans)
        //         cout<<i<<" ";
        //     cout<<endl;
        // }


        return ans;
    }

    int maxSumBST(TreeNode* root) {
        if (root == NULL)
            return 0;

        vector<int> ans = DFS(root);

        return ans[0];
    }
};


/*

Check if BT is a BST

*/

bool check(TreeNode* root, int min, int max) {
    if (root == NULL)
        return 1;

    if (root->val < min || root->val > max)
        return 0;

    return check(root->left, min, root->val - 1) && check(root->right, root->val + 1, max);
}

bool isValidBST(TreeNode* root, TreeNode* left = NULL, TreeNode* right = NULL) {
    if (root == NULL)
        return true;

    if (left && root->val <= left->val)
        return false;

    if (right && root->val >= right->val)
        return false;

    return isValidBST(root->left, left, root) && isValidBST(root->right, root, right);
}

/*

    99. Recover Binary Search Tree

    You are given the root of a binary search tree (BST),
    where exactly two nodes of the tree were swapped by mistake.
    Recover the tree without changing its structure.

    Input: root = [3,1,4,null,null,2]
    Output: [2,1,4,null,null,3]

    Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.

    1, 5, 2, 4, 3

    First Inversion: 5, 2
    Second Inversion: 4, 3

    swap the first of first inversion with the second of second inversion (LOL) to get the sequence.


*/


class Solution {
public:
    TreeNode *first, *second, *prev;

    void recover(TreeNode* root) {
        if (root == NULL)
            return;

        recover(root->left);

        if (first == NULL && root->val < prev->val) first = prev;
        if (first != NULL && root->val < prev->val) second = root;

        prev = root;
        recover(root->right);
    }

    void recoverTree(TreeNode* root) {
        if (root == NULL)
            return;

        first = second = NULL;
        prev = new TreeNode(INT_MIN);
        recover(root);

        swap(first->val, second->val);
    }
};