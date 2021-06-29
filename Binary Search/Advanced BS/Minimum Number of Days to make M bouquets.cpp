/*
    1482.
    Given an integer array bloomDay, an integer m and an integer k.
    We need to make m bouquets. To make a bouquet, you need to use k adjacent flowers from the garden.

    The garden consists of n flowers, the ith flower will bloom in the bloomDay[i] and then can be used in exactly one bouquet.
    Return the minimum number of days you need to wait to be able to make m bouquets from the garden.
    If it is impossible to make m bouquets return -1.

    Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
    Output: 12

    Explanation: We need 2 bouquets each should have 3 flowers.
    Here's the garden after the 7 and 12 days:
    After day 7: [x, x, x, x, _, x, x]
    We can make one bouquet of the first three flowers that bloomed.
    We cannot make another bouquet from the last three flowers that bloomed because they are not adjacent.
    After day 12: [x, x, x, x, x, x, x]
    It is obvious that we can make two bouquets in different ways.

*/


class Solution {
public:

    bool check(vector<int>& day, int m, int k, int X) {
        int cnt = 0, bouquets = 0;

        for (int i = 0; i < day.size(); i++) {
            if (day[i] <= X) {
                cnt++;
            }
            else {
                bouquets += cnt / k;
                cnt = 0;
            }
        }

        bouquets += cnt / k;
        return bouquets >= m;
    }

    int minDays(vector<int>& day, int m, int k) {
        int n = day.size();
        int maxDay = day[0];

        // important step to find min and max day since day vector ain't sorted

        for (auto i : day)
            maxDay = max(maxDay, i);

        int low = 0, high = maxDay + 1, mid;

        while (low < high) {
            mid = (high - low) / 2 + low;

            if (check(day, m, k, mid))
                high = mid;
            else
                low = mid + 1;
        }

        return (low == maxDay + 1) ? -1 : low;
    }
};