/*

    410.
    Given an array nums which consists of non-negative integers and an integer m.
    You can split the array into m non-empty continuous subarrays.

    Write an algorithm to minimize the largest sum among these m subarrays.

    Input: nums = [7,2,5,10,8], m = 2
    Output: 18

    Explanation:
    There are four ways to split nums into two subarrays.
    The best way is to split it into [7,2,5] and [10,8],
    where the largest sum among the two subarrays is only 18.

*/

class Solution {
public:

    bool check(vector<int>& nums, int X, int m) {
        int cnt = 0, curSum = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            if (curSum + nums[i] <= X)
                curSum += nums[i];
            else {
                cnt++;
                curSum = nums[i];
            }
        }

        cnt += curSum <= X;

        return cnt <= m;
    }

    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();

        if (n == 1)
            return nums[n - 1];

        long low = -1, high = 0, mid;
        for (long i : nums)
            low = max(low, i), high += i;

        high += 1;
        while (low < high) {
            mid = (high - low) / 2 + low;

            if (check(nums, mid, m))
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};