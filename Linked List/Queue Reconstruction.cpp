/*
    406. Queue Reconstruction by Height

    You are given an array of people, people,
    which are the attributes of some people in a queue (not necessarily in order).
    Each people[i] = [hi, ki] represents the ith person of height hi with
    exactly ki other people in front who have a height greater than or equal to hi.

    Reconstruct and return the queue that is represented by the input array people.
    The returned queue should be formatted as an array queue,
    where queue[j] = [hj, kj] is the attributes of the jth person in the queue

    Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
    Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
    Explanation:

    Person 0 has height 5 with no other people taller or the same height in front.
    Person 1 has height 7 with no other people taller or the same height in front.
    Person 2 has height 5 with two persons taller or the same height in front, which is person 0 and 1.
    Person 3 has height 6 with one person taller or the same height in front, which is person 1.
    Person 4 has height 4 with four people taller or the same height in front, which are people 0, 1, 2, and 3.
    Person 5 has height 7 with one person taller or the same height in front, which is person 1.

    Hence [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] is the reconstructed queue.


    Sort people by their heights and number of taller ahead them

    1. 7,0
    2. 7,0  7,1
    3. 7,0  6,1  7,1
    4. 5,0  7,0  6,1  7,1
    5. 5,0  7,0  5,2  6,1  7,1
    6. 5,0  7,0  5,2  6,1  4,4  7,1

    Insert taller first
    then shorter
    will not affect the sequence of taller
    and shorter insertion will be based on the currently
    taller once :)

*/

#define v vector<int>

bool comp(v &v1, v &v2) {
    if (v1[0] != v2[0])
        return v1[0] > v2[0];
    return v1[1] < v2[1];
}

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int n = people.size();

        vector<v> ans;

        sort(people.begin(), people.end(), comp);

        list<v> it;

        for (auto p : people) {
            auto pos = it.begin();
            advance(pos, p[1]);

            it.insert(pos, p);
        }

        for (auto i : it)
            ans.push_back(i);

        return ans;
    }
};