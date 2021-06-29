/*

    1008. Construct Binary Search Tree from Preorder Traversal

    Given an array of integers preorder,
    which represents the preorder traversal of a BST (i.e., binary search tree),
    construct the tree and return its root.

    Input: preorder = [8,5,1,7,10,12]
    Output: [8,5,10,1,7,null,12]

            8
          /   \
         5     10
        / \     \
       1   7     12

*/

class Solution {
public:

    TreeNode* construct(vector<int> &p, int s, int e) {
        if (s == e)
            return new TreeNode(p[s]);

        if (s > e)
            return NULL;

        TreeNode *root = new TreeNode(p[s]);

        int lb = s + 1;

        // find the first greater value if no then lb becomes "e + 1"

        while (lb <= e && p[lb] < p[s])
            lb++;

        root->left = construct(p, s + 1, lb - 1);
        root->right = construct(p, lb, e);

        return root;
    }

    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int n = preorder.size();

        if (n == 1)
            return new TreeNode(preorder[n - 1]);

        TreeNode *root = construct(preorder, 0, n - 1);

        return root;
    }
};


/*

    1382. Balance a Binary Search Tree

    Given a binary search tree, return a balanced binary search tree with the same node values.
    A binary search tree is balanced if and only if the depth of the two subtrees of every node never differ by more than 1.

    Construct a BST from a given sorted array or the inorder traversal of the BST;

    Eg-

    1                   2
     \                 / \
      2      -->      1   3
       \                   \
        3                   4
         \
          4

*/

TreeNode* construct(vector<int> &nums, int s, int e) {
    if (s > e)
        return NULL;
    if (s == e)
        return new TreeNode(nums[s]);

    int mid = (e - s) / 2 + s;

    TreeNode *root = new TreeNode(nums[mid]);

    root->left = construct(nums, s, mid - 1);
    root->right = construct(nums, mid + 1, e);

    return root;
}

TreeNode* balanceBST(TreeNode* root) {
    if (root == NULL) {
        return root;
    }

    vector<int> in;
    stack<TreeNode*> s;
    TreeNode *cur = root;

    while (cur != NULL || s.size() > 0) {
        while (cur != NULL) {
            s.push(cur);
            cur = cur->left;
        }

        cur = s.top(); s.pop();
        in.push_back(cur->val);

        cur = cur->right;
    }

    root = construct(in, 0, in.size() - 1);

    return root;
}


/*

    109. Convert Sorted List to Binary Search Tree

    Given the head of a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

    Input: head = [-10,-3,0,5,9]
    Output: [0,-3,9,-10,null,5]

    Explanation:
    One possible answer is [0,-3,9,-10,null,5], which represents the shown height balanced BST.

*/

class Solution {
public:

    TreeNode* construct(ListNode* head) {
        if (head == NULL)
            return NULL;
        if (head->next == NULL)
            return new TreeNode(head->val);


        ListNode* slow = head, *fast = head, *prev = NULL;

        while (fast->next != NULL && fast->next->next != NULL)
            prev = slow, slow = slow->next, fast = fast->next->next;

        if (prev != NULL)
            prev->next = NULL;

        TreeNode* root = new TreeNode(slow->val);

        if (prev)
            root->left = construct(head);

        root->right = construct(slow->next);

        return root;
    }

    TreeNode* sortedListToBST(ListNode* head) {
        if (head == NULL)
            return NULL;

        TreeNode* root = construct(head);

        return root;
    }
};