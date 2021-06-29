Node based binary - tree like structure with the following properties :

1. Each Node in the Left - Subtree is less than the Root;
2. Each Node in the Right - Subtree is greater than the Root;
3. Left and Right Subtree should also be BST;

I. Searching:

Let’s say we want to search for the number, what we’ll do is we’ll start at the root;
and then we will compare the value to be searched with the value of the root;

if it’s equal we are done with the search;
if it’s lesser we know that we need to go to the left subtree;
because in a binary search tree all the elements in the left subtree are lesser
and all the elements in the right subtree are greater;


II. Insertion:

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


III. Some Interesting Facts:

- Inorder traversal of BST always produces sorted output.
- We can construct a BST with only Preorder or Postorder or Level Order traversal.
- Note that we can always get inorder traversal by sorting the only given traversal.
- Number of unique BSTs with n distinct keys is Catalan Number

IV. Deletion:

1. Node to be deleted is the leaf:

Simply remove from the tree;

//		 50                            50
//      /     \         delete(20)      /   \
//     30      70       --------->    30     70
//    /  \    /  \                     \    /  \ 
//  20   40  60   80                   40  60   80

2. Node to be deleted has only one child:

Copy the child to the node and delete the child;

//     50                            50
//  /     \         delete(30)      /   \
// 30      70       --------->    40     70
//   \    /  \                          /  \ 
//   40  60   80                       60   80

3. Node to be deleted has two children;

Find inorder successor of the node. Copy contents of the inorder successor to the node and delete the inorder successor.
Note that inorder predecessor can also be used;

Here, inorder successor is the minimum node in the right substree of the to - be - deleted node;

//     50                            60
//  /     \         delete(50)      /   \
// 40      70       --------->    40    70
//        /  \                            \ 
//       60   80                           80


IV. Advantages of BST over Hash Table;

We can get all keys in sorted order by just doing Inorder Traversal of BST;
This is not a natural operation in Hash Tables and requires extra efforts.

Doing order statistics, finding closest lower and greater elements, doing range queries are easy to do with BSTs;
Like sorting, these operations are not a natural operation with Hash Tables.

BSTs are easy to implement compared to hashing, we can easily implement our own customized BST.
To implement Hashing, we generally rely on libraries provided by programming languages.

With Self - Balancing BSTs, all operations are guaranteed to work in O(Logn) time.
But with Hashing, Θ(1) is average time and some particular operations may be costly, especially when table resizing happens;




#include<bits/stdc++.h>
using namespace std;

struct Node {
	int val;
	Node *left, *right;

	Node(int v) {
		val = v;
		left = right = NULL;
	}
};

Node* search(Node* root, int target) {
	if (root == NULL)
		return root;

	if (root->val == target)
		return root;

	return root->val > target ? search(root->left, target) : search(root->right, target);
}

Node* insert(Node* root, int N) {
	if (root == NULL)
		return new Node(N);

	if (N > root->val)
		root->right = insert(root->right, N);
	else
		root->left = insert(root->left, N);

	return root;
}

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


int main() {

	return 0;
}





