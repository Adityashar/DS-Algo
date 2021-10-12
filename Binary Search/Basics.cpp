/*
	Template //

	low = 0, high = n-1;

	while(low < high):
		mid = (low + high)>>1

		if A[mid] < T:
			low = mid + 1
		else:
			high = mid

	This algorithm converges at the LOW INDEX which is the first occ of target (smallest index value which conforms to the specified condition)
	or the first value greater than target if target not present.

*/

/*
	As a rule of thumb,
	=> use m = l + (r-l)//2 with l = m + 1 and r = m,
	=> use m = r - (r-l)//2 with l = m and r = m - 1.
	This can prevent m from stucking at r (or l) after the updating step.

	It depends on whether you are trying to find the min value satisfying some criteria or the max value.
	=> Use m = l + (r-l)//2 for bisect_left
	=> Use m = r - (r-l)//2 for bisect_right.

*/


/*
	1. Peak Index in a Mountain Array

	Given an integer array arr that is guaranteed to be a mountain.
	Return any i such that arr[0] < arr[1] < ... arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1].

	Input: arr = [24,69,100,99,79,78,67,36,26,19]
	Output: 2

*/

class Solution {
	int badWay(vector<int>& nums) {
		int n = nums.size();
		int low = 0, high = n - 1, mid;
		int ans = -1;

		while (low <= high) {
			mid = (high - low) / 2 + low;

			if (mid - 1 >= 0 && nums[mid] > nums[mid - 1] && mid + 1 < n && nums[mid] > nums[mid + 1])
				return mid;

			if ((mid == 0 || mid - 1 >= 0 && nums[mid] > nums[mid - 1]) && (mid == n - 1 || mid + 1 < n && nums[mid] < nums[mid + 1]))
				low = mid + 1;
			else if ((mid == 0 || mid - 1 >= 0 && nums[mid] < nums[mid - 1]) && (mid == n - 1 || mid + 1 < n && nums[mid] > nums[mid + 1]))
				high = mid - 1;
		}

		return ans;
	}

public:
	int peakIndexInMountainArray(vector<int>& nums) {
		int n = nums.size();
		int low = 0, high = n - 1, mid;
		int ans = -1;

		while (low < high) {
			mid = (high - low) / 2 + low;

			if (mid + 1 < n && nums[mid] < nums[mid + 1])
				low = mid + 1;
			else
				high = mid;
		}

		return low;
	}
};

/*

	2. Find Peak Element
	A peak element is an element that is strictly greater than its neighbors.

	Given an integer array nums, find a peak element, and return its index.
	If the array contains multiple peaks, return the index to any of the peaks.

*/

class Solution {
public:

	int getPeak(vector<int> &nums, int low, int high) {
		if (low > high)
			return -1;

		int mid = (high - low) / 2 + low, n = nums.size();

		if ((mid == 0 || nums[mid] > nums[mid - 1]) && (mid == n - 1 || nums[mid] > nums[mid + 1]))
			return mid;

		if (high == low)
			return -1;

		// if my [mid] < [mid + 1] then put low = mid + 1, since the last index value is -INF

		int leftPeak = getPeak(nums, low, mid);

		if (leftPeak != -1)
			return leftPeak;

		// if my [mid] > [mid + 1] then high = mid, since the first index value is -INF

		int rightPeak = getPeak(nums, mid + 1, high);
		return rightPeak;
	}

	int findPeakElement(vector<int>& nums) {
		int n = nums.size();

		if (n == 1)
			return n - 1;

		int index = getPeak(nums, 0, n - 1);
		return index;
	}
};

/*
	3. Find Peak Element II
	A peak element in a 2D grid is an element that is strictly greater than all of its adjacent neighbors to the left, right, top, and bottom.
	Given a 0-indexed m x n matrix mat where no two adjacent cells are equal.
	Find any peak element mat[i][j] and return the length 2 array [i,j].

	Input: mat = [[10,20,15],[21,30,14],[7,16,32]]
	Output: [1,1]
	Explanation: Both 30 and 32 are peak elements so [1,1] and [2,2] are both acceptable answers.

	Check Row-wise, with a divide-conquer approach to find the peak element and return the cell;

*/

class Solution {
public:

	int getPeak(vector<vector<int>>& mat, int row, int low, int high) {
		if (low > high)
			return -1;

		int mid = (high - low) / 2 + low, n = mat[row].size(), m = mat.size();

		if ((mid == 0 || mat[row][mid] > mat[row][mid - 1]) && (mid == n - 1 || mat[row][mid] > mat[row][mid + 1]) && (row == m - 1 || mat[row][mid] > mat[row + 1][mid]) && (row == 0 || mat[row][mid] > mat[row - 1][mid]))
			return mid;

		if (high == low)
			return -1;

		int leftPeak = getPeak(mat, row, low, mid);
		if (leftPeak != -1)
			return leftPeak;

		int rightPeak = getPeak(mat, row, mid + 1, high);
		return rightPeak;
	}

	int getPeakShort(vector<vector<int>>& mat, int row, int low, int high) {
		int mid;

		while (low < high) {
			mid = (high - low) / 2 + low;

			if (mat[row][mid] < mat[row][mid + 1])
				low = mid + 1;
			else
				high = mid;
		}

		if ((row == 0 || mat[row][low] > mat[row - 1][low]) && (row == mat.size() - 1 || mat[row][low] > mat[row + 1][low]))
			return low;

		return -1;
	}

	vector<int> findPeakGrid(vector<vector<int>>& mat) {
		int n = mat.size();
		int m = mat[0].size();

		for (int i = 0; i < n; i++) {
			int peak = getPeak(mat, i, 0, m - 1);
			if (peak != -1)
				return {i, peak};
		}

		return {0, 0};
	}
};

/*
	4. Search in a rotated Sorted Array I
	There is an integer array nums sorted in ascending order (with distinct values).
	Prior to being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length).
	Such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).

	For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

	Given the array nums after the rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

*/


class Solution {
public:
	int search(vector<int>& nums, int target) {
		int ans = -1;
		int low = 0, high = nums.size() - 1, mid;

		while (low <= high) {
			mid = (high - low) / 2 + low;

			if (nums[mid] == target)
				return mid;

			else if (nums[mid] <= nums[high]) {
				if (target >= nums[mid] && target <= nums[high])
					low = mid + 1;
				else
					high = mid - 1;
			}
			else if (nums[mid] >= nums[low]) {
				if (target <= nums[mid] && target >= nums[low])
					high = mid - 1;
				else
					low = mid + 1;
			}
		}

		return ans;
	}
};

/*
	5. Find minimum in a rotated sorted array
	Given the sorted rotated array nums of unique elements, return the minimum element of this array.

	Input: nums = [3,4,5,1,2]
	Output: 1
	Explanation: The original array was [1,2,3,4,5] rotated 3 times.

*/

class Solution {
public:
	int findMin(vector<int>& nums) {
		int low = 0, high = nums.size() - 1;
		int ans = INT_MAX, mid;

		while (low <= high) {
			mid = (high - low) / 2 + low;

			if (nums[mid] > nums[high]) {
				low = mid + 1;
			}
			else {
				ans = min(ans, nums[mid]), high = mid - 1;
			}
		}

		return ans;
	}
};

/*
	6. Search in a sorted Array with duplicates
	There is an integer array nums sorted in non-decreasing order (not necessarily with distinct values).
	Before being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length),
	such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
	For example, [0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and become [4,5,6,6,7,0,1,2,4,4].

	Given the array nums after the rotation and an integer target, return true if target is in nums, or false if it is not in nums.

*/


class Solution {
public:
	bool search(vector<int>& nums, int target) {
		int low = 0, high = nums.size() - 1, mid;

		while (low < high) {
			mid = (high - low) / 2 + low;
			if (nums[mid] == target)
				return true;

			if (nums[mid] == nums[high] && nums[mid] == nums[low]) {
				low++, high--;
			}
			else if (nums[mid] <= nums[high]) {
				if (target >= nums[mid] && target <= nums[high])
					low = mid + 1;
				else
					high = mid;
			}
			else if (nums[mid] >= nums[low]) {
				if (target <= nums[mid] && target >= nums[low])
					high = mid;
				else
					low = mid + 1;
			}
		}

		return target == nums[low];

	}
};





/*
	7. Find First and Last Position of Element in Sorted Array
	Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.
	If target is not found in the array, return [-1, -1].

*/


class Solution {
public:

	int firstOccurence(vector<int>& nums, int target) {
		int low = 0, high = nums.size() - 1, mid;

		while (low < high) {
			mid = (high - low) / 2 + low;

			if (nums[mid] >= target)
				high = mid;
			else
				low = mid + 1;
		}

		return nums[low] == target ? low : -1;
	}

	int lastOccurence(vector<int>& nums, int target) {
		int low = 0, high = nums.size() - 1, mid;

		while (low < high) {
			mid = (high - low) / 2 + low + 1;

			if (nums[mid] > target)
				high = mid - 1;
			else
				low = mid;
		}

//         if(low == 0)
//             return -1;

//         if(low == nums.size()-1)


		return nums[low] == target ? low : -1;
	}

	vector<int> searchRange(vector<int>& nums, int target) {
		int n = nums.size();
		if (n == 0) {
			return { -1, -1};
		}

		int firstIndex = firstOccurence(nums, target);
		int lastIndex = lastOccurence(nums, target);

		return {firstIndex, lastIndex};
	}
};

// Amongst n number of people in a park. One of them has a virus. Let's assume all the folks are standing in an x-axis line. The positions of people are given as input. A contaminated person can spread the virus up to d distance. Find the minimum and maximum spread of the virus that could occur.
// Input: n = 5, d = 5, [1,3,5,9,14]
// Output: [1, 3]
// minimum spread = 1 by 14, maximum spread = 3 by 5
// I have solved that problem using the Binary Search Method with O(N logN) Time Complexity & O(1) Space Complexity.





