/*

    1552. Magnetic Force between two cows
    In universe Earth C-137, Rick discovered a special form of magnetic force between two balls if they are put in his new invented basket.

    Rick has n empty baskets, the ith basket is at position[i],.
    Morty has m balls and needs to distribute the balls into the baskets such that the minimum magnetic force between any two balls is maximum.

    Rick stated that magnetic force between two different balls at positions x and y is |x - y|.
    Given the integer array position and the integer m. Return the required force.

    Input: position = [1,2,3,4,7], m = 3
    Output: 3
    Explanation: Distributing the 3 balls into baskets 1, 4 and 7 will make the magnetic force between ball pairs [3, 3, 6].
    The minimum magnetic force is 3. We cannot achieve a larger minimum magnetic force than 3.


*/

/*
    Minimum distance between any two balls is maximum
    => place balls such that the adjacent balls are farthest apart
    => return the minimum such adjacent distance when the condition is true

    In gas station problem
    => K more gas stations were to be included to minimize the distance between two adjacent stations
    => we were supposed to return the maximum adjacent distance when the condition is true

*/


class Solution {
public:

    bool check(vector<int>& p, int X, int m) {
        int cnt = 1, n = p.size();
        int prev = p[0];

        for (int i = 1; i < n; i++) {
            if (p[i] - prev >= X)
                cnt++, prev = p[i];
        }

        return cnt >= m;
    }

    int maxDistance(vector<int>& p, int m) {
        int ans = 0, n = p.size();
        sort(p.begin(), p.end());

        int low = 0, high = p[n - 1] - p[0], mid;

        /// bias mid towards the ceil value since answer is in the greater half

        while (low < high) {
            mid = (high - low + 1) / 2 + low;
            if (check(p, mid, m))
                low = mid;
            else
                high = mid - 1;
        }

        return low;
    }
};