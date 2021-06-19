/*

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.

int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache.

If the number of keys exceeds the capacity from this operation, evict the least recently used key.

Eg:

Cache Size = 3;

Pages: 1, 2, 3, 2, 3, 4, 5, 1, 4, 1

CACHE:    1   1,2     1,2,3   1,2,3   1,2,3   4,2,3   4,5,3   4,5,1   4,5,1   4,5,1
LRU:      .   .       .       .       .         .         .   .         .       .

*/


// unordered_map + set

#define pp pair<int, int>
#define f first
#define s second

struct comp {
    bool operator() (int &v1, int &v2) const {
        return v1 > v2;
    }
};

class LRUCache {
public:
    set<pp> lru;
    unordered_map<int, pp> map;
    int time, maxSize;

    LRUCache(int capacity) {
        time = 0;
        maxSize = capacity;
    }

    int get(int key) {
        if (map.find(key) == map.end())
            return -1;

        time++;
        lru.erase({map[key].s, key});
        map[key].s = time;
        lru.insert({time, key});

        return map[key].f;
    }

    void put(int key, int value) {
        time++;

        if (map.find(key) != map.end()) {
            lru.erase({map[key].s, key});
        }
        else {
            if (lru.size() == maxSize) {
                pp temp = *lru.begin();
                map.erase(temp.s);
                lru.erase(temp);
            }
        }
        lru.insert({time, key});
        map[key] = {value, time};
    }
};


// dequeu type DLL with unordered_map

struct Node {
    int val, key;
    Node *prev, *next;

    Node(int v, int k) {
        val = v, key = k;
        prev = next = NULL;
    }
};

class LRUCache {
public:
    unordered_map<int, Node*> map;
    int maxSize, size;

    Node *front, *back;

    LRUCache(int capacity) {
        maxSize = capacity;
        size = 0;
        front = back = NULL;
    }

    int get(int key) {
        if (map.find(key) == map.end())
            return -1;

        // cout<<key<<" u"<<endl;

        // delete node

        Node *temp = map[key];

        if (front == temp)
            return temp->val;

        if (back == temp) {
            if (back->prev)
                back = back->prev;
            else
                return temp->val;
        }

        if (temp->prev)
            temp->prev->next = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;

        temp->prev = temp->next = NULL;

        // deleted node is the new head

        temp->next = front;
        front->prev = temp;
        front = temp;

        map[key] = front;

        // cout<<"use front "<<front->key<<endl;

        return front->val;
    }

    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            map[key]->val = value;
            get(key);
            return;
        }

        size++;
        // cout<<key<<" new"<<endl;
        if (size > maxSize) {
            size--;
            // cout<<"delete back "<<back->key<<endl;
            // erase from map

            map.erase(back->key);

            // update the back

            if (back->prev == NULL)
                front = back = NULL;
            else {
                back->prev->next = NULL;
                back = back->prev;
            }
        }

        Node *temp = new Node(value, key);
        temp->next = front;

        if (front)
            front->prev = temp;
        else
            back = temp;

        front = temp;
        map[key] = front;
    }
};


// STL + splice function

/*

The list::splice() is a built-in function in C++ STL which is used to transfer elements from one list to another.
The splice() function can be used in three ways:

Transfer all the elements of list x into another list at some position.
Transfer only the element pointed by i from list x into the list at some position.
Transfers the range [first, last) from list x into another list at some position.
Syntax:

    list1_name.splice (iterator position, list2)
                    or
    list1_name.splice (iterator position, list2, iterator i)
                    or
    list1_name.splice (iterator position, list2, iterator first, iterator last)

*/