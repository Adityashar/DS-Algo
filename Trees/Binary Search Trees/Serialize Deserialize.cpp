/*

    Serialization is converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer,
    or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

    Design an algorithm to serialize and deserialize a binary search tree.

*/

class Codec {

    void preorder(TreeNode *root, string &s) {
        if (root == NULL)
            return;

        s += to_string(root->val) + " ";

        preorder(root->left, s);
        preorder(root->right, s);
    }

    TreeNode* construct(vector<int> &v, int s, int e) {
        if (s > e)
            return NULL;
        if (s == e)
            return new TreeNode(v[s]);

        TreeNode* root = new TreeNode(v[s]);

        int lb = s + 1;
        while (lb <= e && v[lb] < v[s])
            lb++;

        root->left = construct(v, s + 1, lb - 1);
        root->right = construct(v, lb, e);

        return root;
    }

    void tokenize(string &data, vector<int> &s) {
        int temp = 0;

        for (int i = 0; i < data.size(); i++) {
            if (data[i] == ' ') {
                s.push_back(temp);
                temp = 0;
            }
            else
                temp = temp * 10 + (data[i] - '0');
        }
    }

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s = "";
        preorder(root, s);

        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.size() == 0)
            return NULL;

        vector<int> s;
        tokenize(data, s);

        TreeNode* root = construct(s, 0, s.size() - 1);

        return root;
    }
};
