/*

Design and implement a data structure for a Least Frequently Used (LFU) cache.

Implement the LFUCache class:

LFUCache(int capacity) Initializes the object with the capacity of the data structure.

int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
void put(int key, int value) Update the value of the key if present, or inserts the key if not already present.

When the cache reaches its capacity, it should invalidate and remove the least frequently used key before inserting a new item.

For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be invalidated.
To determine the least frequently used key, a use counter is maintained for each key in the cache.

The key with the smallest use counter is the least frequently used key.
When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). The use counter for a key in the cache is incremented either a get or put operation is called on it.

*/

#define pp pair<int,int>
#define f first
#define s second

class LFUCache {
public:
    int maxSize;
    int size;
    int minFreq;

    unordered_map<int, pp> key2value;       // value, freq
    unordered_map<int, list<int>> freq2key;
    unordered_map<int, list<int>::iterator> key2list;

    LFUCache(int capacity) {
        maxSize = capacity;
        size = 0;
        minFreq = 1;
    }

    void update(int key) {

        // 1. key2value -> get freq -> update by 1

        int freq = key2value[key].s;
        key2value[key].s += 1;

        // 2. Get the iterator to LRU list for given key
        //    Delete this iterator node in the freq2key for 'freq'
        //    push a new node at front of list with 'freq + 1'

        auto it = key2list[key];
        freq2key[freq + 1].push_front(key);
        freq2key[freq].erase(it);

        // 3. if freq is minfreq and freq2key[minFreq] is empty, then update minfreq

        if (freq == minFreq && freq2key[freq].size() == 0)
            minFreq = freq + 1;

        // 4. update the iterator in key to list mapping

        key2list[key] = freq2key[freq + 1].begin();
    }

    int get(int key) {
        if (maxSize == 0 || key2value.find(key) == key2value.end())
            return -1;

        update(key);
        return key2value[key].f;
    }

    void put(int key, int value) {
        if (maxSize == 0)
            return;

        // if key exists then update value
        // invoke the update frequency function

        if (key2value.find(key) != key2value.end()) {
            key2value[key].f = value;
            update(key);
            return;
        }

        // check the size of the cache

        if (size == maxSize) {

            // erase key from key2value
            // erase key from key2list
            // erase key from freq2key
            // if empty then update minFreq

            int key = *freq2key[minFreq].rbegin();
            freq2key[minFreq].pop_back();

            // if(freq2key[minFreq].size() == 0)
            //     minFreq = ?;

            key2value.erase(key);
            key2list.erase(key);

            size--;
        }

        size++;
        int freq = 1;
        key2value[key] = { value, freq };

        if (minFreq > freq)
            minFreq = freq;

        freq2key[freq].push_front(key);
        key2list[key] = freq2key[freq].begin();
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */














