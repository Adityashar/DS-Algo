# Interval Scheduling

## 1. Unweighted Interval Scheduling

#### Examples
435. Non - Overlapping Intervals
646. Maximum Length of Pair Chain

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
     - where val = max(p(i), p(i) + dp(j))
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


## 3. Maximum number of intervals that an interval can intersect

Efficient Approach: The above approach can be optimized by instead of counting the number of intersections, count the number of intervals that do not intersect. The intervals that do not intersect with a particular interval can be divided into two disjoint categories: intervals that fall completely to the left or completely to the right. Using this idea, follow the steps below to solve the problem:

    Create a hashmap, say M, to map the number of intervals that do not intersect with each interval.

    Sort the intervals on the basis of their starting point.

    Traverse the intervals using the variable i

    Initialize ans as -1 to store the index of the first interval lying completely to the right of ith interval.

    Initialize low and high as (i + 1) and (N – 1) and perform a binary search as below:
    Find the value of mid as (low + high)/2.

    If the starting position of interval[mid] is greater than the ending position of interval[i], store the current index mid in ans and then check in the left half by updating high to (mid – 1).

    Else check in the right half by updating low to (mid + 1).

    If the value of ans is not -1, add (N – ans) to M[interval[i]].

    Now, sort the intervals on the basis of their ending point.

    Again, traverse the intervals using the variable i and apply a similar approach as 
    above to find the intervals lying completely to the left of the ith interval.

    After the loop, traverse the map M and store the minimum value in min.

    Print the value of (N – min) as the result.

https://www.geeksforgeeks.org/maximum-number-of-intervals-that-an-interval-can-intersect/


## 4. Meetings Rooms III

Given a list of intervals calendar and a number of available conference rooms. For each query, return true if the meeting can be added to the calendar successfully without causing a conflict, otherwise false. A conference room can only hold one meeting at a time.


Example 1:

Input: calendar = [[1, 2], [4, 5], [8, 10]], rooms = 1, queries = [[4, 5], [5, 6]]
Output: [false, true]


Example 2:

Input:
calendar = [[1, 3], [4, 6], [6, 8], [9, 11], [6, 9], [1, 3], [4, 10]]
rooms = 3
queries = [[1, 9], [2, 6], [7, 9], [3, 5], [3, 9], [2, 4], [7, 10], [5, 9], [3, 10], [9, 10]]
Output: [false, true, false, true, false, true, false, false, false, true]

```python
Find all the time intervals at which all meeting rooms are occupied, this can easily done using dp: rooms[i] means rooms required at ith time. initially all set to 0
iterate over all intervals given.
rooms = [0 for i in range(maxTime)]
for interval in meetings:
    rooms[interval[0]] += 1
    rooms[interval[1]] -= 1


for ind in range(1, len(rooms)):
    rooms[i] += rooms[i-1]

Find all intervals with max number of meetings rooms and keep them in a sorted and non overlapping order.
Given a query [s, e], binary search for where this interval would fit and check if it intersects with interval on left or right.
Time to preprocess : (O(maxTime))
Time to query : (O(log(maxTime)))

Here is the complete code:

def meetingRooms(queries, meetings, k):
    mx = 0
    
    def findGreater(ls, val):
        lo = 0
        hi = len(ls) - 1
        ans = None
        while lo <= hi:
            mid = (lo+hi)//2
            if ls[mid] >= val:
                ans = ls[mid]
                hi = mid-1
            else:
                lo = mid+1
        return ans

    def findSmaller(ls, val):
        lo = 0
        hi = len(ls) - 1
        ans = None
        while lo <= hi:
            mid = (lo+hi)//2
            if ls[mid] < val:
                ans = ls[mid]
                lo = mid+1
            else:
                hi = mid-1
        return ans
        
    for i in meetings:
        mx = max(mx, i[1])

    rooms = [0 for i in range(mx+1)]
    for i in meetings:
        rooms[i[0]] += 1
        rooms[i[1]] -= 1

    ls = []
    if rooms[0] == k:
        ls.append(0)
    for i in range(1, mx+1):
        rooms[i] += rooms[i-1]
        if rooms[i] == k:
            ls.append(i)
            
    print(rooms, ls)
    for q in queries:
        l = findGreater(ls, q[0])
        r = findSmaller(ls, q[1])
        print(q, l, r)
        if l and l >= q[0] and l < q[1]:
            print(False)
            continue

        if r and r >= q[0] and r < q[1]:
            print(False)
            continue

        print(True)

```

