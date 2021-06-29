
/*

    1. Subsets
    Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
    Input: nums = [1,1]
    Output:
    [[],[1],[1,1]]
*/


class Solution {
public:
    vector<vector<int>> ans;

    void dfs(vector<int>& nums, int index, vector<int> &p) {
        int n = nums.size();

        ans.push_back(p);

        for (int i = index; i < n; i++) {
            p.push_back(nums[i]);
            dfs(nums, i + 1, p);
            p.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();
        vector<int> v;
        sort(nums.begin(), nums.end());

        dfs(nums, 0, v);

        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());

        return ans;
    }
};


/*

    2. Permutations
    Given an array nums of distinct integers, return all the possible permutations.
    Input: nums = [1,2]
    Output:
    [[1,2],
     [2,1]]

*/


class Solution {
public:
    vector<vector<int>> ans;

    void dfs(vector<int> &nums, int index) {
        int n = nums.size();

        if (n - 1 == index) {
            ans.push_back(nums);
            return;
        }

        for (int i = index; i < n; i++) {
            swap(nums[index], nums[i]);
            dfs(nums, index + 1);
            swap(nums[index], nums[i]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();

        dfs(nums, 0);

        return ans;
    }
};

/*

    3. Permutations II
    Given an array nums of integers with duplicates, return all the possible permutations.
    Input: nums = [1,1,2]
    Output:
    [[1,1,2],
     [1,2,1],
     [2,1,1]]

*/

class Solution {
public:
    vector<vector<int>> ans;

    void dfs(vector<int> &nums, int index) {
        int n = nums.size();

        if (n - 1 == index) {
            ans.push_back(nums);
            return;
        }

        for (int i = index; i < n; i++) {
            if (i != index && nums[index] == nums[i])
                continue;
            swap(nums[index], nums[i]);
            dfs(nums, index + 1);
            swap(nums[index], nums[i]);
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {

        sort(nums.begin(), nums.end());

        dfs(nums, 0);

        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());

        return ans;
    }
};

/*
    4. Combination Sum I
    Given an array of distinct integers candidates and a target integer target.
    Return a list of all unique combinations of candidates where the chosen numbers sum to target.
    The same number may be chosen from candidates an unlimited number of times (maintain 'index' to select same element multiple times
    and prevent duplicate answers).

    Input: candidates = [2,3,5], target = 8
    Output: [[2,2,2,2],[2,3,3],[3,5]]

*/

class Solution {
public:
    vector<vector<int>> ans;

    void DFS(vector<int> &nums, int target, vector<int> &v, int index) {
        int n = nums.size();

        if (target == 0) {
            ans.push_back(v);
            return;
        }
        if (target < 0)
            return;

        for (int i = index; i < n; i++) {
            v.push_back(nums[i]);
            DFS(nums, target - nums[i], v, i);
            v.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<int> v;

        DFS(nums, target, v, 0);

        return ans;
    }
};

/*
    5. Combination Sum II
    Given an array of integers candidates (with duplicates) and a target integer target.
    Return a list of all unique combinations of candidates where the chosen numbers sum to target.
    The same number may be chosen from candidates ONLY ONCE (proceed with 'index + 1' to prevent duplicate answers).

    Input: candidates = [10,1,2,7,6,1,5], target = 8
    Output:
    [
    [1,1,6],
    [1,2,5],
    [1,7],
    [2,6]
    ]

*/


class Solution {
public:
    vector<vector<int>> ans;

    void DFS(vector<int> &nums, int target, vector<int> &v, int index) {
        int n = nums.size();

        if (target == 0) {
            ans.push_back(v);
            return;
        }
        if (target < 0)
            return;

        for (int i = index; i < n; i++) {
            if (i != index && nums[i - 1] == nums[i])
                continue;
            v.push_back(nums[i]);
            DFS(nums, target - nums[i], v, i + 1);
            v.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<int> v;

        DFS(nums, target, v, 0);

        return ans;
    }
};

/*

    6. Combination Sum III
    Find all valid combinations of k numbers that sum up to n such that the following conditions are true:

    Only numbers 1 through 9 are used.
    Each number is used at most once.
    Return a list of all possible valid combinations.

    Input: k = 3, n = 9
    Output: [[1,2,6],[1,3,5],[2,3,4]]

*/


class Solution {
public:
    vector<vector<int>> ans;

    void DFS(vector<int> &nums, int target, vector<int> &v, int index, int k) {
        int n = nums.size();

        if (target == 0 && k == 0) {
            ans.push_back(v);
            return;
        }
        if (target < 0 || k < 0)
            return;

        for (int i = index; i < n; i++) {
            v.push_back(nums[i]);
            DFS(nums, target - nums[i], v, i + 1, k - 1);
            v.pop_back();
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        vector<int> v;

        DFS(nums, n, v, 0, k);

        return ans;
    }
};

/*

    6. Combination Sum III
    Given an array of distinct integers nums and a target integer target, return the number of possible combinations.

    Input: nums = [1,2,3], target = 4
    Output: 7
    Explanation:
    The possible combination ways are:
    (1, 1, 1, 1)
    (1, 1, 2)
    (1, 2, 1)
    (1, 3)
    (2, 1, 1)
    (2, 2)
    (3, 1)

*/

class Solution {
public:
    vector<unsigned int> dp;        // avoid overflow

    int memo(vector<int>& nums, int target) {
        int n = nums.size();

        if (target == 0)
            return dp[target] = 1;

        if (target < 0)
            return 0;

        if (dp[target] != -1)
            return dp[target];

        int ans = 0;

        for (int i = 0; i < n; i++) {
            ans += memo(nums, target - nums[i]);
        }

        return dp[target] = ans;
    }

    int combinationSum4(vector<int>& nums, int target) {
        dp.resize(target + 1, -1);

        sort(nums.begin(), nums.end());

        for (int i = 1; i <= target; i++) {
            for (int j = 0; j < nums.size(); j++) {
                if (i - nums[j] >= 0) {
                    dp[i] += dp[i - nums[j]];
                }
                else break;
            }
        }

        return dp[target];//memo(nums, target);
    }
};

/*

    7. Combination
    Given two integers n and k, return all possible combinations of k numbers out of the range [1, n].

    Input: n = 4, k = 2
    Output:
    [
      [2,4],
      [3,4],
      [2,3],
      [1,2],
      [1,3],
      [1,4],
    ]

*/

class Solution {
public:
    vector<vector<int>> ans;

    void DFS(int n, int index, int k, vector<int> &p) {
        if (k == 0) {
            ans.push_back(p);
            return;
        }

        for (int i = index; i <= n; i++) {
            p.push_back(i);
            DFS(n, i + 1, k - 1, p);
            p.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        vector<int> path;

        DFS(n, 1, k, path);

        return ans;
    }
};

/*

    8. Letter Combination
    Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.

    Input: digits = "23"
    Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

*/

class Solution {
public:
    vector<string> map, ans;

    void DFS(string &digits, int index, string &t) {
        int n = digits.size();

        if (index == n) {
            ans.push_back(t);
            return;
        }

        int j = digits[index] - '0' - 2;
        for (int i = 0; i < map[j].size(); i++) {
            t.push_back(map[j][i]);
            DFS(digits, index + 1, t);
            t.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        map = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

        if (digits.size() == 0)
            return ans;

        string temp = "";
        DFS(digits, 0, temp);


        return ans;
    }
};