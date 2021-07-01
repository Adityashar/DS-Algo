# Interval Scheduling

## 1. Unweighted Interval Scheduling

#### Examples
- 435. Non - Overlapping Intervals
- 646. Maximum Length of Pair Chain

### 646

You are given an array of n pairs pairs
where pairs[i] = [lefti, righti] and lefti < righti.

A pair p2 = [c, d] follows a pair p1 = [a, b] if b < c.
A chain of pairs can be formed in this fashion.

Return the length longest chain which can be formed.



#### Greedy Approach:
   1. Sort by the end times
   2. take a current interval CUR
   3. iterate over the intervals I
   4. if CUR overlaps with I then increase the count
      else make CUR = I

	##### Proof
	When pairA[1] >= pairB[0], we have to choose carefully, because that means:
        - either we only append pairA to the chain,
	    - or we only append pairB to the chain.
	
	Append either pairA or pairB will increment the length of the chain by 1.
	
	However: (note: cur is the tail of the chain)
	    - appending pairA will have cur = pairA[1],
	    - appending pairB will have cur = pairB[1].
	    - And pairA[1] < pairB[1]
  
	Apparently, we shall append pairA first because that way we expose a smaller tail which has a better opportunity to append more future pairs.

```cpp
bool comp(vector<int> &v1, vector<int> &v2) {
	if (v1[1] != v2[1])
		return v1[1] < v2[1];

	return v1[0] < v2[0];
}

class Solution {
public:
	int findLongestChain(vector<vector<int>>& pairs) {
		int n = pairs.size();

		if (n <= 1)
			return n;

		sort(pairs.begin(), pairs.end(), comp);

		int cnt = 0;
		vector<int> cur = pairs[0];

		for (int i = 1; i < n; i++) {
			if (cur[1] < pairs[i][0])
				cur = pairs[i];
			else
				cnt++;
		}

		return n - cnt;
	}
};
```

#### DP Approach
   1. Sort either by starts or ends
   2. dp(i) -> Length of longest chain ending at i
   3. ans cals the max length of the chain using the max lengths of each of the indices


```cpp
bool comp(vector<int> &v1, vector<int> &v2) {
    if(v1[1] != v2[1])
        return v1[1] < v2[1];
    
    return v1[0] < v2[0];
}

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        
        if(n <= 1) 
            return n;
        
        sort(pairs.begin(), pairs.end(), comp);
        vector<int> dp(n);
        dp[0] = 1;
        
        int ans = 0;
        
        for(int i=1; i<n; i++) {
            dp[i] = 1;
            for(int j=i-1; j>=0; j--) {
                if(pairs[i][0] > pairs[j][1])
                    dp[i] = max(dp[i], 1 + dp[j]);
				
				// if false, use the max of j
				// pair[i] would not be included
				// else
				//     dp[i] = max(dp[i], dp[j]);
				// this gives the answer at n-1 index
				// no need to maintain *ans*	
            }
            ans = max(ans, dp[i]);
        }
        
        return ans;
    }
};
```

## 2. Weighted Interval Scheduling

Each interval has a specific weight assigned to itself. But Greedy algorithm can fail spectacularly if arbitrary weights are allowed. So that's when DP comes in.



### Examples
1235. Maximum Profit in Job Scheduling

We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].

You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.


Input: 
    startTime = [1,2,3,4,6], 
    endTime = [3,5,10,6,9], 
    profit = [20,20,100,70,60]

Output: 150
Explanation: The subset chosen is the first, fourth and fifth job. 
Profit obtained 150 = 20 + 70 + 60.


#### 1. DP Approach
   - sort by the endtimes
   - maintain dp(i) -> maxProfit till this index (incl / not incl)
   - for each i 
     - search for the last index in [0, i-1] such that ET[j] <= ST[i]
     - dp(i) is max(dp(i-1), val) 
     - where val = max(dp(j), p(i) + dp(j))
   - dp(n-1) gives the max profit value when all the n-1 indices are  considered


```cpp
class Solution {
public:
    
    // highest index such that endTime[j] <= X
    // biased to the right side
	
    int position(vector<vector<int>> &e, int n, int X) {
        int low = 0, high = n-1, mid;
        
        while(low < high) {
            mid = (high - low)/2 + low + 1;
            
            if(e[mid][0] <= X)
                low = mid;
            else
                high = mid - 1;
        }
        
        return e[low][0] <= X? low: -1;
    }
    
    int jobScheduling(vector<int>& st, vector<int>& et, vector<int>& p) {
        int n = st.size();
        
        if(n == 1)
            return p[n-1];
        
        vector<vector<int>> e;
        
        for(int i=0; i<n; i++) 
            e.push_back({et[i], st[i], p[i]});
        
        sort(e.begin(), e.end());
        vector<int> dp(n);
        
        dp[0] = e[0][2];
        
        for(int i=1; i<n; i++) {
            int pos = position(e, i, e[i][1]);
            
            int val = (pos == -1)? e[i][2]: e[i][2] + dp[pos];
            dp[i] = max(dp[i-1], val);
        }
        
        return dp[n-1];
    }
};

```


#### 2. Failed BruteForce Approach
```cpp

#define pp pair<int, int>
#define f first
#define s second

class Solution {
public:
    vector<long> dp;
    vector<int> position;
    
    int lowerbound(vector<vector<int>> &e, int s, int X) {
        int n = e.size();
        int low = s, high = n-1, mid;
        int pos = n;
        
        while(low < high) {
            mid = (high - low)/2 + low;
            
            if(e[mid][0] >= X)
                high = mid;
            else
                low = mid + 1;
        }
        
        if(low == n-1)
            low = e[n-1][0] >= X? low: n;
        
        return low;
    }
    
    long DFS(vector<vector<int>> &e, int End, int index) {
        long ans = 0;
        
        if(dp[index] != -1)
            return dp[index];
        
        int pos = position[index];
        
        for(int i=pos; i<e.size(); i++) {
            ans = max(ans, DFS(e, e[i][1], i));
        }
        
        return dp[index] = ans + e[index][2];
    }
    
    int jobScheduling(vector<int>& st, vector<int>& et, vector<int>& p) {
        int n = st.size();
        
        if(n == 1)
            return p[n-1];
        
        vector<vector<int>> e;
        dp.resize(n, -1);
        
        for(int i=0; i<n; i++) 
            e.push_back({st[i], et[i], p[i]});
        
        sort(e.begin(), e.end());
        
        for(int i=0; i<n; i++) {
            position.push_back(lowerbound(e, i+1, e[i][1]));
        }
        
        long ans = 0;
        
        for(int i=0; i<n; i++) {
            ans = max(ans, DFS(e, e[i][1], i));
        }
        
        return ans;
    }
};

```