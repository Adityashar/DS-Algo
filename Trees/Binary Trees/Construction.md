# Construction

## 1. Preorder and Inorder
Time Complexity - O(N*N)
Space Complexity - O(H)

1) Pick an element from Preorder. Increment a Preorder Index Variable (preIndex in below code) to pick the next element in the next recursive call. 
2) Create a new tree node tNode with the data as the picked element. 
3) Find the picked element’s index in Inorder. Let the index be inIndex. 
4) Call buildTree for elements before inIndex and make the built tree as a left subtree of tNode. 
5) Call buildTree for elements after inIndex and make the built tree as a right subtree of tNode. 
6) return tNode.

```cpp
/*

Inorder sequence: D B E A F C 
Preorder sequence: A B D E C F

      A
    /   \
   /     \
D B E     F C

         A
       /   \
     /       \
    B         C
   / \        /
 /     \    /
D       E  F

*/

node* buildTree(char in[], char pre[], int inStrt, int inEnd)
{
    static int preIndex = 0;
 
    if (inStrt > inEnd)
        return NULL;
 
    /* Pick current node from Preorder
    traversal using preIndex
    and increment preIndex */
    node* tNode = newNode(pre[preIndex++]);
 
    /* If this node has no children then return */
    if (inStrt == inEnd)
        return tNode;
 
    /* Else find the index of this node in Inorder traversal */
    
    /* Use an unordered_map to reduce TC */
    
    int inIndex = search(in, inStrt, inEnd, tNode->data);
 
    /* Using index in Inorder traversal, construct left and
    right subtress */
    tNode->left = buildTree(in, pre, inStrt, inIndex - 1);
    tNode->right = buildTree(in, pre, inIndex + 1, inEnd);
 
    return tNode;
}

```

## 2. Postorder and Inorder

```cpp

Node* buildUtil(int in[], int post[], int inStrt,
    int inEnd, int* pIndex, unordered_map<int, int>& mp)
{
    // Base case
    if (inStrt > inEnd)
        return NULL;
 
    /* Pick current node from Postorder traversal 
    using postIndex and decrement postIndex */
    int curr = post[*pIndex];
    Node* node = newNode(curr);
    (*pIndex)--;
 
    /* If this node has no children then return */
    if (inStrt == inEnd)
        return node;
 
    /* Else find the index of this node in Inorder
    traversal */
    int iIndex = mp[curr];
 
    /* Using index in Inorder traversal, construct
    left and right subtress */
    node->right = buildUtil(in, post, iIndex + 1,
                            inEnd, pIndex, mp);
    node->left = buildUtil(in, post, inStrt,
                           iIndex - 1, pIndex, mp);
 
    return node;
}

```

## 3. Preorder and Postorder
- It is not possible to construct a general Binary Tree from preorder and postorder traversals. But if know that the Binary Tree is Full, we can construct the tree without ambiguity.

- Approach

1. Let us consider the two given arrays as pre[] = {1, 2, 4, 8, 9, 5, 3, 6, 7} and post[] = {8, 9, 4, 5, 2, 6, 7, 3, 1}; 

2. In pre[], the leftmost element is root of tree. Since the tree is full and array size is more than 1. The value next to 1 in pre[], must be left child of root. So we know 1 is root and 2 is left child. 

3. How to find the all nodes in left subtree? We know 2 is root of all nodes in left subtree. All nodes before 2 in post[] must be in left subtree. 

4. Now we know 1 is root, elements {8, 9, 4, 5, 2} are in left subtree, and the elements {6, 7, 3} are in right subtree. 


```cpp

node* constructTreeUtil (int pre[], int post[], int* preIndex, int l, int h, int size)
{
    // Base case
    if (*preIndex >= size || l > h)
        return NULL;
 
    // The first node in preorder traversal is root. So take the node at
    // preIndex from preorder and make it root, and increment preIndex
    node* root = newNode ( pre[*preIndex] );
    ++*preIndex;
 
    // If the current subarray has only one element, no need to recur
    if (l == h)
        return root;
 
    // Search the next element of pre[] in post[]
    int i;
    for (i = l; i <= h; ++i)
        if (pre[*preIndex] == post[i])
            break;
 
    // Use the index of element found in postorder to divide
        // postorder array in two parts. Left subtree and right subtree
    if (i <= h)
    {
        root->left = constructTreeUtil (pre, post, preIndex,
                                                l, i, size);
        root->right = constructTreeUtil (pre, post, preIndex,
                                                 i + 1, h-1, size);
    }
 
    return root;
}

```

## 4. Tree from Bracket String

- We know first character in string is root. Substring inside the first adjacent pair of parenthesis is for left subtree and substring inside second pair of parenthesis is for right subtree as in the below diagram. 

- We need to find the substring corresponding to left subtree and substring corresponding to right subtree and then recursively call on both of the substrings. 

- To find the index of closing parenthesis of left subtree substring, use a stack. Let the found index be stored in index variable. 

```cpp
/*

Input : "4(2(3)(1))(6(5))"
Output : 4 2 3 1 6 5
Explanation :
           4
         /   \
        2     6
       / \   / 
      3   1 5 

*/

// function to return the index of close parenthesis
int findIndex(string str, int si, int ei)
{
    if (si > ei)
        return -1;
 
    // Inbuilt stack
    stack<char> s;
 
    for (int i = si; i <= ei; i++) {
 
        // if open parenthesis, push it
        if (str[i] == '(')
            s.push(str[i]);
 
        // if close parenthesis
        else if (str[i] == ')') {
            if (s.top() == '(') {
                s.pop();
 
                // if stack is empty, this is
                // the required index
                if (s.empty())
                    return i;
            }
        }
    }
    // if not found return -1
    return -1;
}
 
// function to construct tree from string
Node* treeFromString(string str, int si, int ei)
{
    // Base case
    if (si > ei)
        return NULL;
 
    // new root
    Node* root = newNode(str[si] - '0');
    int index = -1;
 
    // if next char is '(' find the index of
    // its complement ')'
    if (si + 1 <= ei && str[si + 1] == '(')
        index = findIndex(str, si + 1, ei);
 
    // if index found
    if (index != -1) {
 
        // call for left subtree
        root->left = treeFromString(str, si + 2, index - 1);
 
        // call for right subtree
        root->right
            = treeFromString(str, index + 2, ei - 1);
    }
    return root;
}



```

## 5. Binary Tree Serialization

```cpp
class Codec {
    
    void preorder(TreeNode *root, string &s) {
        if(root == NULL) {
            s += "N";
            return;
        }
        
        s += to_string(root->val) + ' ';
        
        preorder(root->left, s);
        
        s += ' ';
        
        preorder(root->right, s);
    }
    
    int value(string &s, int &i) {
        int negative = 1;
        int n = s.size();
        
        if(s[i] == '-')
            negative = -1, i++;
        
        long val = 0;
        while(i < n && isdigit(s[i])) {
            val = val * 10 + (s[i]-'0');
            i++;
        }
        
        return val * negative;
    }
    
    TreeNode* makeTree(string &s, int &i) {
        int n = s.size();
        
        if(n == i)
            return NULL;
        
        if(s[i] == 'N') {
            i++;
            return NULL;
        }
        
        TreeNode *root = new TreeNode(value(s, i));
        i++;
        
        root->left = makeTree(s, i);
        i++;
        
        root->right = makeTree(s, i);
        
        return root;
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
        int index = 0;
        
        TreeNode* root = makeTree(data, index);
        
        return root;
    }
};


```

## 6. LL to Binary Tree

- We are mainly given level order traversal in sequential access form. We know head of linked list is always is root of the tree. 

- We take the first node as root and we also know that the next two nodes are left and right children of root. So we know partial Binary Tree. 

- The idea is to do Level order traversal of the partially built Binary Tree using queue and traverse the linked list at the same time. At every step, we take the parent node from queue, make next two nodes of linked list as children of the parent node, and enqueue the next two nodes to queue.

```cpp

void convertList2Binary(ListNode *head, BinaryTreeNode* &root)
{
    // queue to store the parent nodes
    queue<BinaryTreeNode *> q;
 
    // Base Case
    if (head == NULL) {
        root = NULL; // Note that root is passed by reference
        return;
    }
 
    // 1.) The first node is always the root node, and add it to the queue
    root = newBinaryTreeNode(head->data);
    q.push(root);
 
    // advance the pointer to the next node
    head = head->next;
 
    // until the end of linked list is reached, do the following steps
    while (head)
    {
        // 2.a) take the parent node from the q and remove it from q
        BinaryTreeNode* parent = q.front();
        q.pop();
 
        // 2.c) take next two nodes from the linked list. We will add
        // them as children of the current parent node in step 2.b. Push them
        // into the queue so that they will be parents to the future nodes
        BinaryTreeNode *leftChild = NULL, *rightChild = NULL;

        leftChild = newBinaryTreeNode(head->data);
        q.push(leftChild);
        
        head = head->next;

        if (head) {
            rightChild = newBinaryTreeNode(head->data);
            q.push(rightChild);

            head = head->next;
        }
 
        // 2.b) assign the left and right children of parent
        parent->left = leftChild;
        parent->right = rightChild;
    }
}

```