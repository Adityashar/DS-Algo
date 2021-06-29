#include <bits/stdc++.h>
using namespace std;

/*
	1. Count Subarrays with sum in the range [L, R]

	=> (Count of Subarrays with sum <= R) - (Count of Subarrays with sum <= L-1)
	=> Keep adding the window size to the count when the condition is true
*/


int count(vector<int> &nums, int K) {
	int n = nums.size(), ws = 0, we = 0;
	int sum = 0, cnt = 0;

	while (we < n) {
		sum += nums[we++];

		while (sum > K) {
			;
			sum -= nums[ws++];
		}

		cnt += we - ws;
	}

	return cnt;
}

/*

	2. Subarray Product Less Than K

	Given an array of integers nums and an integer k.
	Return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than k.

	Input: nums = [10,5,2,6], k = 100
	Output: 8
	Explanation: The 8 subarrays that have product less than 100 are:
	[10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]

*/

int numSubarrayProductLessThanK(vector<int>& nums, int k) {
	int n = nums.size(), ws = 0, we = 0;

	if (k == 0)
		return 0;

	long cnt = 0, product = 1;

	while (we < n) {
		product *= nums[we++];

		while (ws < we && product >= k)
			product /= nums[ws++];

		cnt += we - ws;
	}

	return cnt;
}

/*

	3. Subarrays with K Different Integers

	Given an array nums of positive integers, call a (contiguous, not necessarily distinct) subarray of nums good
	if the number of different integers in that subarray is exactly k.

	(For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)
	Return the number of good subarrays of nums.

	Input: nums = [1,2,1,2,3], k = 2
	Output: 7
	Explanation:

	Subarrays formed with exactly 2 different integers:
	[1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].

*/

int countSubArraysAtmostKDifferent(vector<int> &nums, int k) {
	int ans = 0;
	int start = 0, end = 0, n = nums.size();
	unordered_map<int, int> map;

	while (end < n) {
		map[nums[end]]++;

		while (map.size() > k) {
			// cout<<ans<<" ";
			// ans += end - start;
			if (map[nums[start++]]-- == 1)
				map.erase(nums[start - 1]);
		}
		end++;
		ans += end - start;
	}

	// while(start < end)
	//     ans += end - start, start++;

	// cout<<ans<<endl;
	return ans;
}

int subarraysWithKDistinct(vector<int>& nums, int k) {

	int kdifferent = countSubArraysAtmostKDifferent(nums, k);
	int kminusdifferent = k == 1 ? 0 : countSubArraysAtmostKDifferent(nums, k - 1);

	return kdifferent - kminusdifferent;
}

/*

	4. Number of Subarrays with Bounded Maximum

	Given an integer array nums and two integers left and right.
	Return the number of contiguous non-empty subarrays
	such that the value of the maximum array element in that subarray is in the range [left, right].

	Input: nums = [2,1,4,3], left = 2, right = 3
	Output: 3

	Explanation:
	There are three subarrays that meet the requirements: [2], [2, 1], [3].

*/


int elementsLessThanK(vector<int> &nums, int K) {
	int cnt = 0, start = 0;

	for (int i = 0; i < nums.size(); i++) {
		if (nums[i] > K)
			start = i + 1;
		else
			cnt += i - start + 1;
	}

	return cnt;
}

int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
	return elementsLessThanK(nums, right) - elementsLessThanK(nums, left - 1);
}


/*

	209. Minimum Size Subarray Sum

	Given an array of positive integers nums and a positive integer target,
	return the minimal length of a contiguous subarray [numsl, numsl+1, ..., numsr-1, numsr]
	of which the sum is greater than or equal to target.

	If there is no such subarray, return 0 instead.

	Input: target = 7, nums = [2,3,1,2,4,3]
	Output: 2

	Explanation: The subarray [4,3] has the minimal length under the problem constraint.

*/

class Solution {
public:
	int minSubArrayLen(int target, vector<int>& nums) {
		int wStart = 0, wEnd = 0, n = nums.size(), winSum = 0, minSize = n + 1, size = 0;

		while (wEnd < n) {
			winSum += nums[wEnd];
			wEnd++;
			size++;

			if (winSum >= target) {
				do {
					minSize = min(minSize, size);
					winSum -= nums[wStart];
					wStart++;
					size--;
				} while (winSum >= target);
			}
		}

		return minSize == n + 1 ? 0 : minSize;
	}
};

// using binary search

int minSubArrayLen(int target, vector<int>& nums) {
	int n = nums.size(), minSize = n + 1;
	vector<int> sums;
	sums.push_back(0);

	for (auto i : nums)
		sums.push_back(sums.back() + i);

	for (int i = 0; i < n; i++) {
		if (sums[i + 1] - target == 0)
			minSize = min(minSize, i + 1);

		else if (sums[i + 1] > target) {
			int ub = upper_bound(sums.begin(), sums.end() + i + 1, sums[i + 1] - target) - sums.begin();

			minSize = min(minSize, i - ub + 2);
		}
	}

	return minSize == n + 1 ? 0 : minSize;
}




int main() {

	vector<int> arr = {2, 3, 5, 8};
	int l = 4, r = 13;

	cout << count(arr, r) - count(arr, l - 1);

	return 0;
}