# Everything to know before the Interview

## Theory

Node based binary - tree like structure with the following properties :

1. Each Node in the Left - Subtree is less than the Root;
2. Each Node in the Right - Subtree is greater than the Root;
3. Left and Right Subtree should also be BST;

### I. Searching:

Let’s say we want to search for the number, what we’ll do is we’ll start at the root;
and then we will compare the value to be searched with the value of the root;

if it’s equal we are done with the search;
if it’s lesser we know that we need to go to the left subtree;
because in a binary search tree all the elements in the left subtree are lesser
and all the elements in the right subtree are greater;


### II. Insertion:

// 	    100                               100
//     /   \        Insert 40            /    \
//   20     500    --------->          20     500
//  /  \                              /  \  
// 10   30                           10   30
//                                           \   
//                                           40

A new key is always inserted at the leaf. We start searching a key from the root until we hit a leaf node.
Once a leaf node is found, the new node is added as a child of the leaf node.

TC: O(N) in worst case: Skewed tree with a height equal to N, O(Height) average case;


### III. Some Interesting Facts:

- Inorder traversal of BST always produces sorted output.
- We can construct a BST with only Preorder or Postorder or Level Order traversal.
- Note that we can always get inorder traversal by sorting the only given traversal.
- Number of unique BSTs with n distinct keys is Catalan Number

### IV. Deletion:

#### 1. Node to be deleted is the leaf:

Simply remove from the tree;

//		 50                            50
//      /     \         delete(20)      /   \
//     30      70       --------->    30     70
//    /  \    /  \                     \    /  \ 
//  20   40  60   80                   40  60   80

#### 2. Node to be deleted has only one child:

Copy the child to the node and delete the child;

//     50                            50
//  /     \         delete(30)      /   \
// 30      70       --------->    40     70
//   \    /  \                          /  \ 
//   40  60   80                       60   80

#### 3. Node to be deleted has two children;

Find inorder successor of the node. Copy contents of the inorder successor to the node and delete the inorder successor.
Note that inorder predecessor can also be used;

Here, inorder successor is the minimum node in the right substree of the to - be - deleted node;

//     50                            60
//  /     \         delete(50)      /   \
// 40      70       --------->    40    70
//        /  \                            \ 
//       60   80                           80


### IV. Advantages of BST over Hash Table;

We can get all keys in sorted order by just doing Inorder Traversal of BST;
This is not a natural operation in Hash Tables and requires extra efforts.

Doing order statistics, finding closest lower and greater elements, doing range queries are easy to do with BSTs;
Like sorting, these operations are not a natural operation with Hash Tables.

BSTs are easy to implement compared to hashing, we can easily implement our own customized BST.
To implement Hashing, we generally rely on libraries provided by programming languages.

With Self - Balancing BSTs, all operations are guaranteed to work in O(Logn) time.
But with Hashing, Θ(1) is average time and some particular operations may be costly, especially when table resizing happens;


## 2. BST Implemetation

```cpp
struct Node {
	int val;
	Node *left, *right;

	Node(int v) {
		val = v;
		left = right = NULL;
	}
};

/* 
    Searching is an O(logN) operation.
*/

Node* search(Node* root, int target) {
	if (root == NULL)
		return root;

	if (root->val == target)
		return root;

	return root->val > target ? search(root->left, target) : search(root->right, target);
}

/* 
    Insertion is an O(logN) operation.
*/

Node* insert(Node* root, int N) {
	if (root == NULL)
		return new Node(N);

	if (N > root->val)
		root->right = insert(root->right, N);
	else
		root->left = insert(root->left, N);

	return root;
}


/* 
    Deletion is an O(logN) operation.
*/

Node* deleteNode(Node* root, int key) {
	if (root == NULL)
		return root;

	if (root->val > key)
		root->right = deleteNode(root->right, key);

	else if (root->val < key)
		root->left = deleteNode(root->left, key);

	else {

		// single child / no child

		if (root->left == NULL) {
			Node *temp = root->right;
			delete root;
			return temp;
		}

		else if (root->right == NULL) {
			Node *temp = root->left;
			delete root;
			return temp;
		}

		/*
			delete 1

		Node *succesor = inorderSuccesor(root->right);
		root->val = successor->val;

		// delete succesor
		root->right = deleteNode(root->right, successor->val);

		*/

		//	delete 2

		Node *parent = root;
		Node *succ = root->right;

		while (succ->left) {
			parent = succ;
			succ = succ->left;
		}

		if (parent == root)
			parent->right = succ->right;
		else
			parent->left = succ->right;

		root->key = succ->key;

		delete succ;
	}

	return root;
}

```


## 3. Construction

Different ways of constructing a BST, from existing arrays and linked lists.

### I. Construct Binary Search Tree from Preorder Traversal

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

```cpp

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

```

### II. Construct BST from inorder traversal (or) Balance a BST

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

```cpp

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

```

### III. Sorted List to BST

Convert Sorted List to Binary Search Tree

Given the head of a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

Input: head = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]

Explanation:
One possible answer is [0,-3,9,-10,null,5], which represents the shown height balanced BST.


```cpp

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

```

### IV. BST to MinHeap

Given a binary search tree which is also a complete binary tree. The problem is to convert the given BST into a Min Heap with the condition that all the values in the left subtree of a node should be less than all the values in the right subtree of the node.

Input :          4
               /   \
              2     6
            /  \   /  \
           1   3  5    7  

Output :        1
              /   \
             2     5
           /  \   /  \
          3   4  6    7 

The given BST has been transformed into a
Min Heap.
All the nodes in the Min Heap satisfies the given
condition, that is, values in the left subtree of
a node should be less than the values in the right
subtree of the node. 

#### Algorithm:

- Create an array arr[] of size n, where n is the number of nodes in the given BST.
- Perform the inorder traversal of the BST and copy the node values in the arr[] in sorted order.
- Now perform the preorder traversal of the tree.
- While traversing the root during the preorder traversal, one by one copy the values from the array arr[] to the nodes.

## Serialize and Deserialize BST

Serialization is converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer,
or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree.


```cpp


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

```