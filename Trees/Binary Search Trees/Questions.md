# Important Questions

## 1. LCA

```cpp

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == NULL) return root;
        
        while(root) {
            
            if(root->val > p->val && root->val > q->val)
                root = root->left;
            
            else if(root->val < p->val && root->val < q->val)
                root = root->right;
            
            else return root;
        }
         
//         if(root->val > p->val && root->val > q->val) 
//             return lowestCommonAncestor(root->left, p, q);
        
//         if(root->val < p->val && root->val < q->val)
//             return lowestCommonAncestor(root->right, p, q);
        
        return root;
    }

```

## 2. Valid BST

```cpp

    bool isValidBST(TreeNode* root, TreeNode* left = NULL, TreeNode* right = NULL) {
        if(root == NULL)
            return true;
        
        if(left && root->val <= left->val)
            return false;
        
        if(right && root->val >= right->val)
            return false;
        
        return isValidBST(root->left, left, root) && isValidBST(root->right, root, right);
    }

```

## 3. Recover BST

You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.

Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.

https://leetcode.com/submissions/detail/512970150/

```cpp

    TreeNode *first, *second, *prev;
    
    void recover(TreeNode* root) {
        if(root == NULL)
            return;
        
        recover(root->left);
        
        if(first == NULL && root->val < prev->val) first = prev;
        if(first != NULL && root->val < prev->val) second = root;
        
        prev = root;    
        recover(root->right);
    }
    
    void recoverTree(TreeNode* root) {
        if(root == NULL)
            return;
        
        first = second = NULL;  
        prev = new TreeNode(INT_MIN);
        recover(root);
        
        swap(first->val, second->val);
    }

```

## 4. Trim a BST

Given the root of a binary search tree and the lowest and highest boundaries as low and high, trim the tree so that all its elements lies in [low, high]. Trimming the tree should not change the relative structure of the elements that will remain in the tree (i.e., any node's descendant should remain a descendant). It can be proven that there is a unique answer.

Return the root of the trimmed binary search tree. Note that the root may change depending on the given bounds.

Input: root = [1,0,2], low = 1, high = 2
Output: [1,null,2]

```cpp

    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if(root == NULL)
            return NULL;
        
        if(root->val < low)
            return trimBST(root->right, low, high);
        
        if(root->val > high)
            return trimBST(root->left, low, high);
        
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
        
        return root;
    }

```

## 5. BST Iterator

Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):

- BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
- boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
- int next() Moves the pointer to the right, then returns the number at the pointer.

BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);

bSTIterator.next();    // return 3
bSTIterator.next();    // return 7
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 9
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 15
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 20
bSTIterator.hasNext(); // return False


```cpp

class BSTIterator {
public:
    stack<TreeNode*> s;
    bool rev;
    
    void inorderStep(TreeNode* root, stack<TreeNode*> &s) {
        while(root) 
            s.push(root), root = root->left;
    }
    
    BSTIterator(TreeNode* root) {
        inorderStep(root, s);
        rev = false;
    }
    
    int next() {
        TreeNode* v = s.top();
        s.pop();
        
        inorderStep(v->right, s);
        
        return v->val;
    }
    
    bool hasNext() {
        return  s.size() > 0;
    }
};

```

## 6. Two Sum

Given the root of a Binary Search Tree and a target number k, return true if there exist two elements in the BST such that their sum is equal to the given target.

Input: root = [5,3,6,2,4,null,7], k = 9
Output: true

### Map

```cpp
    unordered_map<int, int> map;
    
    bool findTarget(TreeNode* root, int k) {
        if(root == NULL)
            return false;
        
        if(map.find(k - root->val) != map.end())
            return true;
        
        map[root->val]++;
        
        return findTarget(root->left, k) || findTarget(root->right, k);
    }
```

### Two pointer
The idea is to use a sorted array to save the values of the nodes in the BST by using an inorder traversal. Then, we use two pointers which begins from the start and end of the array to find if there is a sum k.

```cpp

    bool findTarget(TreeNode* root, int k) {
        vector<int> nums;
        inorder(root, nums);
        for(int i = 0, j = nums.size()-1; i<j;){
            if(nums[i] + nums[j] == k)return true;
            (nums[i] + nums[j] < k)? i++ : j--;
        }
        return false;
    }
    
    void inorder(TreeNode* root, vector<int>& nums){
        if(root == NULL)return;
        inorder(root->left, nums);
        nums.push_back(root->val);
        inorder(root->right, nums);
    }

```

### Iterator
Maintain a forward and backward iterator and follow the two pointer approach.

```cpp

class Iterator {
    stack<TreeNode*> s;
    bool dir;
    
    void successor(TreeNode* root) {
        while(root != NULL) {
            s.push(root);
            root = dir? root->left: root->right;
        }
    }
    
public:
    Iterator(TreeNode* root, bool d) {
        dir = d;
        successor(root);
    }
    
    bool hasNext() {
        return s.size() > 0;
    }
    
    int peek() {
        return s.top()->val;
    }
    
    void next() {
        TreeNode* top = s.top();
        s.pop();
        
        dir? successor(top->right): successor(top->left);
    }
    
};

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        
        Iterator *left = new Iterator(root, 1);
        Iterator *right = new Iterator(root, 0);
        
        while(left->hasNext() && right->hasNext()) {
            if(left->peek() >= right->peek())
                return false;
            
            if(left->peek() + right->peek() == k)
                return true;
            
            if(left->peek() + right->peek() > k)
                right->next();
            else 
                left->next();
        }
        
        return false;
    }
};

```

## 7. Kth Largest in a BST

### O(N) Space 
Store the inorder and print the (k-1)th index of the container.

### O(H) Space
- Use iterative/recursive inorder
- maintain an iterator i
- increament i when a node has been visited (print)
- return when i == k

### O(1) Space
Morris Traversal with an iterator i.

```cpp

int morris(TreeNode* root, int k) {

    TreeNode* cur = root;
    int i = 0;

    while(cur != NULL) {
        if(cur->left == NULL) {

            cout<<cur->val<<" ";
            
            if(i++ == k)
                return cur->val;

            cur = cur->right;
        }
        else {

            TreeNode* predecessor = cur->left;
            while(cur != predecessor->right && predecessor->right != NULL)
                predecessor = predecessor->right;

            if(predecessor->right == cur) {
                predecessor->right = NULL;

                cout<<cur->val<<" ";
                
                if(i++ == k)
                    return cur->val;

                cur = cur->right;
            }
            else {
                predecessor->right = cur;
                cur = cur->left;
            }
        }
    }

    return -1;
}

```


- Rank of an element in a stream
- Find the largest BST subtree in a given Binary Tree
- Find the closest element in Binary Search Tree
- Print BST keys in given Range | O(1) Space
- Count BST nodes that lie in a given range
- Count BST subtrees that lie in given range