# Hashing

### Problem Statement
Suppose we want to design a system for storing employee records keyed using phone numbers. And we want following queries to be performed efficiently:

- Insert a phone number and corresponding information.
- Search a phone number and fetch the information.
- Delete a phone number and related information.


### *Different Approaches that can be used:*
1. **Array of phone numbers and records.**
    Search - O(logN) when sorted or O(N)
    Insertion - Linear time
    Deletion - Linear time 

2. **Linked List of phone numbers and records.**
    Search - O(logN) when sorted or O(N)
    Insertion - Constant time
    Deletion - Constant time 

3. **Balanced binary search tree with phone numbers as keys.**
    Search - O(logN)
    Insertion - O(logN)
    Deletion - O(logN) 

4. **Direct Access Table.**
    The DAT maintains a large array and uses the phone numbers as the indices. n entry in array is NIL if phone number is not present, else the array entry stores pointer to records corresponding to phone number. Time complexity wise this solution is the best among all, we can do all operations in O(1) time.

    This solution has many practical limitations. 
    - First problem with this solution is extra space required is huge. 
    - Another problem is an integer in a programming language may not store n digits.

    For example if phone number is n digits, we need O(m * 10^n) space for table where m is size of a pointer to record.


##### *Hashing* is an improvement over Direct Access Table. The idea is to use hash function that converts a given phone number or any other key to a smaller number and uses the small number as index in a table called hash table.

#### Hash Function
A function that converts a given big phone number to a small practical integer value. The mapped integer value is used as an index in hash table.
A good hash function should have following properties
1) Efficiently computable.
2) Should uniformly distribute the keys.

#### Collision Handling
Since a hash function gets us a small number for a big key, there is possibility that two keys result in same value. The situation where a newly inserted key maps to an already occupied slot in hash table is called **collision** and must be handled using some **collision handling** technique. An important observation is Birthday Paradox. *With only 23 persons, the probability that two people have the same birthday is 50%.* 

#### 1. Trivial Hashing
Given a limited size array which may contain both positive and negative numbers, Index Mapping is used where values are taken as the indices in the big array.
To handle a negative number, the idea is to use a 2D array of size hash[MAX+1][2].

#### 2. Separate Chaining 
The idea is to make each cell of hash table point to a linked list of records that have same hash function value. 

Example. Consider the hash function, F(key) = key % 7 and keys = [50, 700, 76, 85, 92, 73, 101].
         Final Table: 
         0 -> 700
         1 -> 50 -> 84 -> 92
         2
         3 -> 73 -> 101
         4
         5
         6 -> 76
         

##### Advantages
1) Hash table never fills up, we can always add more elements to the chain. 
2) Less sensitive to the hash function or load factors. 
3) It is mostly used when it is unknown how many and how frequently keys may be inserted or deleted. 

##### Disadvantages: 
1) Cache performance of chaining is not good as keys are stored using a linked list. Open addressing provides better cache performance as everything is stored in the same table. 
2) Wastage of Space (Some Parts of hash table are never used) 
3) If the chain becomes long, then search time can become O(n) in the worst case. 
4) Uses extra space for links. 

Data Structures For Storing Chains: 
l -> load factor
This Load Factor needs to be kept low, so that number of entries at one index is less and so is the complexity almost constant, i.e., O(1).

when the load factor increases to more than its pre-defined value (default value of load factor is 0.75), the complexity increases. So to overcome this, the size of the array is increased (doubled) and all the values are hashed again and stored in the new double sized array to maintain a low load factor and low complexity.

- Linked lists
    Search: O(l) where l = length of linked list
    Delete: O(l)
    Insert: O(l)
    Not cache friendly
- Dynamic Sized Arrays ( Vectors in C++, ArrayList in Java, list in Python)
    Search: O(l) where l = length of array
    Delete: O(l)
    Insert: O(l)
    Cache friendly
- Self Balancing BST ( AVL Trees, Red Black Trees)
    Search: O(log(l))
    Delete: O(log(l))
    Insert: O(l)
    Not cache friendly



#### 3. Open Addressing
In Open Addressing, all elements are stored in the hash table itself. So at any point, the size of the table must be greater than or equal to the total number of keys. 

- Insert(k): Keep probing until an empty slot is found. Once an empty slot is found, insert k. 
- Search(k): Keep probing until slot’s key doesn’t become equal to k or an empty slot is reached. 
- Delete(k): If we simply delete a key, then the search may fail. So slots of deleted keys are marked specially as “deleted”. 
             The insert can insert an item in a deleted slot, but the search doesn’t stop at a deleted slot.


1) Linear Probing
In linear probing, we linearly probe for next slot. For example, the typical gap between two probes is 1 as seen in the example below. 
Let hash(x) be the slot index computed using a hash function and S be the table size.

   If slot hash(x) % S is full, then we try (hash(x) + 1) % S
   If (hash(x) + 1) % S is also full, then we try (hash(x) + 2) % S
   If (hash(x) + 2) % S is also full, then we try (hash(x) + 3) % S 
   ..................................................
   ..................................................

Challenges in Linear Probing :

**Primary Clustering**: One of the problems with linear probing is Primary clustering, many consecutive elements form groups and it starts taking time to find a free slot or to search for an element.  
**Secondary Clustering**: Secondary clustering is less severe, two records only have the same collision chain (Probe Sequence) if their initial position is the same.


2) Quadratic Probing
We look for i*i ‘th slot in i’th iteration.  
    let hash(x) be the slot index computed using hash function.  
    If slot hash(x) % S is full, then we try (hash(x) + 1*1) % S
    If (hash(x) + 1* 1) % S is also full, then we try (hash(x) + 2*2) % S
    If (hash(x) + 2* 2) % S is also full, then we try (hash(x) + 3*3) % S
    ..................................................
    ..................................................


3) Double Hashing
We use another hash function hash2(x) and look for i*hash2(x) slot in i’th rotation. 
    let hash(x) be the slot index computed using hash function.  
    If slot hash(x) % S is full, then we try (hash(x) + 1*hash2(x)) % S
    If (hash(x) + 1* hash2(x)) % S is also full, then we try (hash(x) + 2*hash2(x)) % S
    If (hash(x) + 2* hash2(x)) % S is also full, then we try (hash(x) + 3*hash2(x)) % S
    ..................................................
    ..................................................

```cpp

// Hash table size
#define TABLE_SIZE 13
  
// Used in second hash function.
#define PRIME 7
  
class DoubleHash {
    // Pointer to an array containing buckets
    int* hashTable;
    int curr_size;
  
public:
    // function to check if hash table is full
    bool isFull()
    {
  
        // if hash size reaches maximum size
        return (curr_size == TABLE_SIZE);
    }
  
    // function to calculate first hash
    int hash1(int key)
    {
        return (key % TABLE_SIZE);
    }
  
    // function to calculate second hash
    int hash2(int key)
    {
        return (PRIME - (key % PRIME));
    }
  
    DoubleHash()
    {
        hashTable = new int[TABLE_SIZE];
        curr_size = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
            hashTable[i] = -1;
    }
  
    // function to insert key into hash table
    void insertHash(int key)
    {
        // if hash table is full
        if (isFull())
            return;
  
        // get index from first hash
        int index = hash1(key);
  
        // if collision occurs
        if (hashTable[index] != -1) {
            // get index2 from second hash
            int index2 = hash2(key);
            int i = 1;
            while (1) {
                // get newIndex
                int newIndex = (index + i * index2) % TABLE_SIZE;
  
                // if no collision occurs, store
                // the key
                if (hashTable[newIndex] == -1) {
                    hashTable[newIndex] = key;
                    break;
                }
                i++;
            }
        }
  
        // if no collision occurs
        else
            hashTable[index] = key;
        curr_size++;
    }
  
    // function to search key in hash table
    void search(int key)
    {
        int index1 = hash1(key);
        int index2 = hash2(key);
        int i = 0;
        while (hashTable[(index1 + i * index2) % TABLE_SIZE] != key) {
            if (hashTable[(index1 + i * index2) % TABLE_SIZE] == -1) {
                cout << key << " does not exist" << endl;
                return;
            }
            i++;
        }
        cout << key << " found" << endl;
    }
  
    // function to display the hash table
    void displayHash()
    {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (hashTable[i] != -1)
                cout << i << " --> "
                     << hashTable[i] << endl;
            else
                cout << i << endl;
        }
    }
};


```


**Performance of Open Addressing:**
m = Number of slots in the hash table
n = Number of keys to be inserted in the hash table
 
Load factor α = n/m  ( < 1 )

Expected time to search/insert/delete < 1/(1 - α) 

So Search, Insert and Delete take (1/(1 - α)) time.