/*
	1. Kth smallest element in two sorted arrays
*/

// O(N)

int kthSmallest(vector<int> &A, vector<int> &B, int k) {
	int i = 0, j = 0;
	int m = A.size(), n = B.size();

	while (i < m && j < n) {
		if (A[i] < B[j]) {
			k--;
			if (k == 0)
				return A[i];
			i++;
		}
		else {
			k--;
			if (k == 0)
				return B[j];
			j++;
		}
	}

	while (i < m) {
		k--;
		if (k == 0)
			return A[i];
		i++;
	}

	while (j < n) {
		k--;
		if (k == 0)
			return B[j];
		j++;
	}

	return -1;
}

// O(log(N*M))

// 0-Indexed K, high is not included in the search space

int kthSmallest(vector<int> &A, vector<int> &B, int low1, int high1, int low2, int high2, int k) {
	if (low1 == high1)
		return B[k];
	if (low2 == high2)
		return A[k];

	int mid1 = (high1 - low1) / 2 + low1;
	int mid2 = (high2 - low2) / 2 + low2;

	if (mid1 - low1 + mid2 - low2 < k)	{
		if (A[mid1] < B[mid2])
			return kthSmallest(A, B, mid1 + 1, high1, low2, high2, k - (mid1 - low1 - 1));
		else
			return kthSmallest(A, B, low1, high1, mid2 + 1, high1, k - (mid2 - low2 - 1));
	}
	else {
		if (A[mid1] < B[mid2])
			return kthSmallest(A, B, low1, high1, low2, mid2, k);
		else
			return kthSmallest(A, B, low1, mid1, low2, high2, k);
	}
}

/*

	2. Median of two Sorted Arrays
	Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

*/

class Solution {
public:

	double Median(vector<int> &A, vector<int> &B, int n, int m) {
		int size = n + m, low = 0, high = n;
		int partitionX = (low + high) / 2;
		int partitionY = (n + m + 1) / 2 - partitionX;

		while (low <= high) {

			int Aleft = partitionX == 0 ? INT_MIN : A[partitionX - 1];
			int Aright = partitionX == n ? INT_MAX : A[partitionX];
			int Bleft = partitionY == 0 ? INT_MIN : B[partitionY - 1];
			int Bright = partitionY == m ? INT_MAX : B[partitionY];

			if (Aleft > Bright)
				high = partitionX - 1;

			else if (Bleft > Aright)
				low = partitionX + 1;

			else if (Aleft <= Bright && Bleft <= Aright) {
				if (size % 2)
					return max(Aleft, Bleft);
				else
					return ((max(Aleft, Bleft)) + min(Aright, Bright)) / 2.0;
			}

			partitionX = (low + high) / 2;
			partitionY = (n + m + 1) / 2 - partitionX;
		}

		return 0;
	}

	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int n1 = nums1.size(), n2 = nums2.size();

		if (n1 < n2)
			return Median(nums1, nums2, n1, n2);

		return Median(nums2, nums1, n2, n1);
	}
};