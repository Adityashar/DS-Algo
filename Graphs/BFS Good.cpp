/*
    1. Open the Lock

    You have a lock in front of you with 4 circular wheels.

    Each wheel has 10 slots:

    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'.

    The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'.
    Each move consists of turning one wheel one slot.

    The lock initially starts at '0000', a string representing the state of the 4 wheels.
    You are given a list of deadends dead ends, meaning if the lock displays any of these codes,

    the wheels of the lock will stop turning and you will be unable to open it.

    Given a target representing the value of the wheels that will unlock the lock,
    return the minimum total number of turns required to open the lock, or -1 if it is impossible.

    => DFS => TLE => Re-traversal of same paths arising from different nodes or since min path has been asked, use BFS :)

*/

#define INF 999999

class Solution {
public:
    unordered_set<string> set;
    vector<int> v;

    int DFS(int index, string &p, string &target, int cur) {
        if (index == 4)
            return p == target ? 0 : INF;

        int val1 = INF, val2 = INF, val3 = INF;
        v[index] |= 1 << cur;

        // move to next lock

        p.push_back(cur + '0');

        if (p.size() != 4 || (p.size() == 4 && set.find(p) == set.end()))
            val1 = DFS(index + 1, p, target, 0);

        p.pop_back();

        // check cur + 1 on current lock


        int next = ((cur + 1) % 10 + 10) % 10;
        if (!(v[index] & (1 << next))) {
            val2 = DFS(index, p, target, next);
        }

        // check cur - 1 on current lock

        next = ((cur - 1) % 10 + 10) % 10;

        if (!(v[index] & (1 << next))) {
            val3 = DFS(index, p, target, next);
        }

        v[index] &= ~(1 << cur);

        int ans = min({val1, val2, val3});

        return ans == INF ? INF : ans + 1;
    }

    int openLock(vector<string>& deadends, string target) {
        for (auto i : deadends)
            set.insert(i);

        v.resize(4, 0);
        string path = "0000";
        // int val = DFS(0, path, target, 0);

        if (set.find(path) != set.end())
            return -1;

        queue<string> q;
        q.push("0000");

        int level = 0;

        while (q.size() > 0) {
            int s = q.size();

            while (s--) {
                string cur = q.front(); q.pop();

                if (target == cur)
                    return level;

                for (int i = 0; i < 4; i++) {
                    char c = cur[i];
                    int next = (cur[i] - '0' + 1) % 10;
                    int prev = ((cur[i] - '0' - 1) % 10 + 10) % 10;

                    cur[i] = next + '0';
                    if (set.find(cur) == set.end())
                        q.push(cur), set.insert(cur);

                    cur[i] = prev + '0';
                    if (set.find(cur) == set.end())
                        q.push(cur), set.insert(cur);

                    cur[i] = c;
                }
            }
            if (q.size() == 0)
                break;

            level++;
        }

        return -1;
    }
};

















