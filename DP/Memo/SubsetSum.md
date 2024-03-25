# Subset Sums

1. Subset that have the sum K
2. Partition Equal Subset Sum
3. Partition K Equal Subset Sum
4. https://discuss.codechef.com/t/count-all-ordered-pairs-with-bitwise-and-equals-to-zero/36081

## Example
#### 416. Partition Equal Subset Sum
Given a non - empty array nums containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

Input: nums = [1, 5, 11, 5]
              Output: true
Explanation:

  The array can be partitioned as [1, 5, 5] and [11].

```cpp
	class Solution {
	public:
		vector<vector<int>> dp;

		bool DFS(vector<int> &nums, int n, int sum) {
			if (n == 0 && sum == 0)
				return dp[n][sum] = true;
			if (n == 0)
				return dp[n][sum] = false;
			if (sum == 0)
				return dp[n][sum] = true;

			if (dp[n][sum] != -1)
				return dp[n][sum];

			if (sum - nums[n - 1] >= 0 && DFS(nums, n - 1, sum - nums[n - 1]))
				return dp[n][sum] = true;

			return dp[n][sum] = DFS(nums, n - 1, sum);
		}

		bool canPartition(vector<int>& nums) {
			int n = nums.size();
			long sum = 0;

			if (n <= 1)
				return false;

			for (auto i : nums)
				sum += i;

			if (sum % 2)
				return false;

			sum >>= 1;
			// dp.resize(n + 1, vector<int>(sum + 1, -1));
			// DFS(nums, n, sum);

			vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1));

			for (int i = 0; i <= n; i++) {
				for (long j = 0; j <= sum; j++) {

					if (i == 0 && j == 0)
						dp[i][j] = true;
					else if (i == 0)
						dp[i][j] = false;
					else if (j == 0)
						dp[i][j] = true;
					else {
						dp[i][j] = dp[i - 1][j];

						if (j - nums[i - 1] >= 0)
							dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
					}
				}

			}

			return dp[n][sum];
		}
	};

```
