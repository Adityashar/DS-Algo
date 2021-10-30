# Traversals

## Recursive

### Preorder, Postorder, Inorder
Time Complexity: O(n) 
Space Complexity: O(H) 

```cpp

    void printPreorder(Node* node)
    {
        if (node == NULL)
            return;
    
        // cout << node->data << " ";        ---> Preorder
    
        printPreorder(node->left);

        // cout << node->data << " ";        ---> Inorder

        printPreorder(node->right);

        // cout << node->data << " ";        ---> Postorder
    }

```

## Iterative
Time Complexity: O(n) 

### Space - O(N)

#### 1. Preorder

```cpp

    void printPreorder(Node* node) {
        if (node == NULL)
            return;
    
        stack<Node*> s;
        Node* cur = node;


        while(cur != NULL || s.size() > 0) {
            while(cur != NULL) {
  
            // cout << cur->data << " ";        ---> Preorder
    
                if(cur->right)
                    s.push(cur->right);
                
                cur = cur->left;
            } 

            if(s.size() > 0) {
                cur = s.top();
                s.pop();
            }
        }
    }

```

#### 2. Inorder

```cpp

    void printInorder(Node* node) {
        if (node == NULL)
            return;
    
        stack<Node*> s;
        Node* cur = node;


        while(cur != NULL || s.size() > 0) {
            while(cur != NULL) {
                s.push(cur);
                cur = cur->left;
            } 

            cur = s.top();
            s.pop();
        
            // cout << cur->data << " ";        ---> Inorder
    
            cur = cur->right;
        }
    }

```

#### 3. Postorder

HLR -> HRL -> LRH

```cpp
    // 2 Stacks

    void printPostorder(Node* node) {
        if (node == NULL)
            return;
    
        stack<Node*> s, revS;
        Node* cur = node;


        while(cur != NULL || s.size() > 0) {
            while(cur != NULL) {
                
                revS.push(cur);

                if(cur->left)
                    s.push(cur->left);
                
                cur = cur->right;
            } 

            if(s.size() > 0) {
                cur = s.top();
                s.pop();
            }
        }

        // pop and print revS
    }

    // 1 Stack

    void printPostorder(Node* node) {
        
        stack<Node*> s;
        Node* cur = node;

        while(cur != NULL || s.size() > 0) {
            while(cur != NULL) {
                if(cur->right)
                    s.push(cur->right);

                s.push(cur);
                cur = cur->left;
            }

            cur = s.top();
            s.pop();

            if(cur->right && cur->right == s.top()) {
                Node *top = s.top();
                s.pop();
                s.push(cur);
                cur = top;
            }
            else {
                // print cur
                cur = NULL;
            }
        }

    }

```


### Space - O(1)

Morris Traversal

```cpp

    void MorrisTraversal(struct tNode* root)
    {
        struct tNode *current, *pre;
    
        if (root == NULL)
            return;
    
        current = root;
        while (current != NULL) {
    
            if (current->left == NULL) {
                printf("%d ", current->data);
                current = current->right;
            }
            else {
    
                /* Find the inorder predecessor of current */
                pre = current->left;
                while (pre->right != NULL
                    && pre->right != current)
                    pre = pre->right;
    
                /* Make current as the right child of its
                inorder predecessor */
                if (pre->right == NULL) {
                    pre->right = current;
                    current = current->left;
                }
    
                /* Revert the changes made in the 'if' part to
                restore the original tree i.e., fix the right
                child of predecessor */
                else {
                    pre->right = NULL;
                    printf("%d ", current->data);
                    current = current->right;
                } /* End of if condition pre->right == NULL */
            } /* End of if condition current->left == NULL*/
        } /* End of while */
    }

```


## Level Order Traversal
Time Complexity - O(N)
Space Complexity - O(W) or O(H)

```cpp

    // recursive

    class Solution {
    public:
        
        void order(TreeNode* root, vector<vector<int>> &ans, int l) {
            if(root == NULL)
                return;
            
            if(ans.size() < l+1) {
                ans.push_back({root->val});
            }
            else {
                ans[l].push_back(root->val);
            }
            
            order(root->left, ans, l+1);
            order(root->right, ans, l+1);
        }
        
        vector<vector<int>> levelOrder(TreeNode* root) {
            vector<vector<int>> ans;
            
            order(root, ans, 0);
            
            return ans;
        }
    };

    // iterative

    class Solution {
    public:
        vector<vector<int>> levelOrder(TreeNode* root) {
            vector<vector<int>> lo;
            
            if(root == NULL)
                return lo;
            
            queue<TreeNode*> q;
            q.push(root);
            int l = 0;
            
            while(q.size() > 0) {
                int s = q.size();
                vector<int> v;
                
                while(s--) {
                    TreeNode* cur = q.front();
                    q.pop();
                    
                    v.push_back(cur->val);
                    
                    if(cur->left)
                        q.push(cur->left);
                    if(cur->right)
                        q.push(cur->right);
                }
                l++;
                if(v.size() > 0)
                    lo.push_back(v);
            }
            
            return lo;
        }
    };

```

### Reverse Levelorder

```cpp
/*
            1
           / \
          2   3
         / \   \
        4  5    6
          /
         7 

    7
    4, 5, 6
    2, 3
    1

    or

    7, 4, 5, 6, 2, 3, 1

*/

    class Solution {
    public:
        vector<int> levelOrder(TreeNode* root) {
            vector<int> lo;
            
            if(root == NULL)
                return lo;
            
            queue<TreeNode*> q;
            q.push(root);
            int l = 0;
            
            while(q.size() > 0) {
                int s = q.size();
                
                while(s--) {
                    TreeNode* cur = q.front();
                    q.pop();
                    
                    lo.push_back(cur->val);
                    
                    if(cur->right)
                        q.push(cur->right);
                    if(cur->left)
                        q.push(cur->left);
                }
                l++;
            }
            
            reverse(lo.begin(), lo.end());

            return lo;
        }
    };

```

### Zigzag Levelorder

```cpp
/*
            1
           / \
          2   3
         / \   \
        4  5    6
          /
         7 

        1
        3, 2
        4, 5, 6
        7

*/

    vector<int> findSpiral(Node *root)
    {
        int d = 1;
        
        deque<Node*> q;
        q.push_back(root);
        
        vector<int> ans;
        
        while(q.size()) {
            int s = q.size();
            
            while(s--) {
                if(!d) {
                    Node* cur = q.front(); q.pop_front();
                    
                    ans.push_back(cur->data);
                    
                    if(cur->right)
                        q.push_back(cur->right);
                    if(cur->left)
                        q.push_back(cur->left);
                }
                else {
                    Node* cur = q.back(); q.pop_back();
                    
                    ans.push_back(cur->data);
                    
                    if(cur->left)
                        q.push_front(cur->left);
                    if(cur->right)
                        q.push_front(cur->right);
                }
            }
            
            d = !d;
        }
        
        return ans;
    }

```

## Diagonal Traversal
All elements or nodes in the "right" lie on the same diagonal.
All Left Nodes lie on the (d + 1)th diagonal.

```cpp

void diagonalPrintUtil(Node* root, int d,
                map<int, vector<int>> &diagonalPrint)
{
    // Base case
    if (!root)
        return;
 
    // Store all nodes of same
    // line together as a vector
    diagonalPrint[d].push_back(root->data);
 
    // Increase the vertical
    // distance if left child
    diagonalPrintUtil(root->left, d + 1, diagonalPrint);
 
    // Vertical distance remains
    // same for right child
    diagonalPrintUtil(root->right, d, diagonalPrint);
}

```

## Vertical Traversal
Each Node has a unique (row, col).
For each col, store the nodes row-wise.

```cpp


    map<int, vector<pp>> map;
    
    void vertical(TreeNode* root, int level, int col) {
        if(root == NULL)
            return ;
        
        map[col].push_back({level, root->val});
        
        vertical(root->left, level+1, col-1);
        vertical(root->right, level+1, col+1);
    }
    
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        vector<vector<int>> res;
        
        if(root == NULL)
            return res;
        
        vertical(root, 0, 0);
        
        for(auto it: map) {
            sort(it.s.begin(), it.s.end());
            vector<int> v;
            
            for(auto j: it.s)
                v.push_back(j.s);
            
            res.push_back(v);
        }    
        
        return res;
    }

```

## Boundary Traversal