/*
    1. Beautiful Arrangement

    Suppose you have n integers labeled 1 through n.
    A permutation of those n integers perm (1-indexed) is considered a beautiful arrangement if for every i (1 <= i <= n),
    either of the following is true:

        perm[i] is divisible by i.
        i is divisible by perm[i].

    Given an integer n, return the number of the beautiful arrangements that you can construct.

*/

class Solution {
public:

    int cnt;

    void DFS(int n, int &v, int index) {
        if (index == n + 1) {
            cnt++;
            return;
        }

        for (int i = 1; i <= n; i++) {
            if (!(v & 1 << (i - 1)) && (index % i == 0 || i % index == 0)) {
                v |= 1 << (i - 1);
                DFS(n, v, index + 1);
                v &= ~(1 << (i - 1));
            }
        }
    }

    int countArrangement(int n) {
        if (n == 1)
            return 1;

        cnt = 0;
        int v = 0;

        DFS(n, v, 1);

        return cnt;
    }
};