/*

    LC84. Largest Rectangle in Histogram
    LC239. Sliding Window Maximum
    LC739. Daily Temperatures
    LC862. Shortest Subarray with Sum at Least K
    LC901. Online Stock Span
    LC907. Sum of Subarray Minimums
    Given a element A[i], find the nearest element larger/smaller than it

*/


/*

    862. Shortest Subarray with Sum at Least K

    Return the length of the shortest, non-empty, contiguous subarray of nums with sum at least k.

    Window can't be used since there are negative numbers in the array.

    K:                110
    Array:            [34, 53, -51, 50, 60]
    PrefixSums:    [0, 34, 87, 36, 86, 146]

    Find the nearest element to i in prefix array such that the condition is true.

    Intuition:

    In the monotone Queue prefixSums are maintained in an increasing order
    such that the indices also increase on going from left to right
    (high index, lower values)

    For each prefixSum(i), find the largest prefixSum(topDQ) inside the queue such that the condition:

    prefix(i) - prefix(topDQ) >= K

    Update the answer for each index.

    DQ:

    1.    [34]
    2.    [34, 87]
    3.    [34, 36] -> (87,1) has been popped to maintain monotone since (36,2) both has lower value and higher index.
    4.    [34, 36, 86]
    5.    [86, 146] -> (34, 0) has been popped, (36, 2) has been popped, since they're satisfying the given condition

*/

class Solution {
public:

    void push(deque<int> &dq, vector<long> &sums, int i) {

        while (dq.size() > 0 && sums[i] <= sums[dq.back()])
            dq.pop_back();

        dq.push_back(i);
    }

    int shortestSubarray(vector<int>& nums, int k) {
        int ans = INT_MAX, n = nums.size();

        deque<int> dq;

        vector<long> sums;
        sums.push_back(0);

        for (auto i : nums)
            sums.push_back(sums.back() + i);

        for (int i = 1; i <= n; i++) {
            if (sums[i] >= k)
                ans = min(ans, i);

            // search in deque largest sum for which condition remains true;

            while (dq.size() > 0 && sums[i] - sums[dq.front()] >= k) {
                ans = min(ans, i - dq.front());
                dq.pop_front();
            }

            // push cur sums into the dq

            push(dq, sums, i);
        }

        return ans != INT_MAX ? ans : -1;
    }
};


/*

    239. Sliding Window Maximum

    You are given an array of integers nums,
    there is a sliding window of size k which is moving from the very left of the array to the very right.
    You can only see the k numbers in the window.
    Each time the sliding window moves right by one position.

    Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
    Output: [3,3,5,5,6,7]
    Explanation:

    Window position                Max
    ---------------               -----
    [1  3  -1] -3  5  3  6  7       3
     1 [3  -1  -3] 5  3  6  7       3
     1  3 [-1  -3  5] 3  6  7       5
     1  3  -1 [-3  5  3] 6  7       5
     1  3  -1  -3 [5  3  6] 7       6
     1  3  -1  -3  5 [3  6  7]      7


    Maintain a monotonic queue such that it keeps the decreasing order of element maximums
    as the index increases.


*/


void push(deque<int> &dq, vector<int> &nums, int i) {
    while (dq.size() > 0 && nums[dq.back()] <= nums[i])
        dq.pop_back();

    dq.push_back(i);
}

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();

    vector<int> ans;
    deque<int> dq;

    for (int i = 0; i < k; i++) {
        push(dq, nums, i);
    }

    ans.push_back(nums[dq.front()]);

    for (int i = 0; i < n - k; i++) {
        while (dq.size() > 0 && dq.front() <= i) {
            dq.pop_front();
        }

        push(dq, nums, i + k);
        ans.push_back(nums[dq.front()]);
    }

    return ans;
}



/*

    907. Sum of Subarray Minimums

    Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr.

    Input: arr = [3,1,2,4]
    Output: 17
    Explanation:

    Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
    Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
    Sum is 17.

    Suppose the queue state is -
    ... 2, 5, 8....
    then the value at index 5 is the smallest for the interval starting at index 3 uptill the end

*/



#define M 1000000007

class Solution {
public:
    int sumSubarrayMins(vector<int>& nums) {
        int n = nums.size() + 1;

        // pushing -1 into the deque for calculating the count of subarrays in which the
        // current front of the deque is minimum

        deque<int> dq;
        dq.push_back(-1);

        // pushing -1 into the nums array for handling the last iteration
        // when all the elements inside the queue are in an increasing order
        nums.push_back(-1);

        long long ans = 0;

        for (int i = 0; i < n; i++) {

            while (dq.size() > 1 && nums[i] <= nums[dq.back()]) {
                int cur = dq.back();
                dq.pop_back();

                ans = ans + 1LL * nums[cur] * (i - cur) * (cur - dq.back());
                ans %= M;
            }

            dq.push_back(i);
        }

        return ans % M;
    }
};



