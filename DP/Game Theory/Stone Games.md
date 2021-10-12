# Stone Game


## Optimal Strategy for a Game
Consider a row of n coins of values v1 . . . vn, where n is even. We play a game against an opponent by alternating turns. In each turn, a player selects either the first or last coin from the row, removes it from the row permanently, and receives the value of the coin. Determine the maximum possible amount of money we can definitely win if we move first.


#### Example
1. [5, 3, 7, 10]    
    -> v1 = 10 + func(5, 3, 7) = 15
    -> v2 = 5 + func(3, 7, 10) = 12

    -> v = max(v1, v2) = 15

2. [8, 15, 3, 7]    
    -> v1 = 8 + func(15, 3, 7) = 15
    -> v2 = 7 + func(8, 15, 3) = 22

    -> v = max(v1, v2) = 22


#### Approach
As both the players are equally strong, both will try to reduce the possibility of winning of each other. Now let’s see how the opponent can achieve this.

- if the player chooses ith value, then the opponent has to make a choice from [i+1, .... j] values. The opponent would intend to choose the extreme which leaves the player with the minimum value.

    Vi + min(F(i+2, j), F(i+1, j-1));

- if the player chooses jth value, then the opponent has to make a choice from [i, .... j-1] values. 

    Vj + min(F(i+1, j-1), F(i, j-2));

    F(i, j) -> Max value that can be collected when the [i, ... j] coins are available.
    F(i, j) = Max(Vi + min(F(i+2, j), F(i+1, j-1)), 
                  Vj + min(F(i+1, j-1), F(i, j-2)))


```cpp

int maxSum(vector<int> &piles) {
    int n = piles.size();

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for(int gap = 0; gap < n; gap++) {
        for(int i=0, j=gap; j < n; i++, j++) {

            if(gap == 0)
                dp[i][j] = piles[i];
            
            else if(gap == 1)
                dp[i][j] = max(piles[i], piles[j]);
            
            else {
                int v1 = piles[i] + min(dp[i+2][j], dp[i+1][j-1]);
                int v2 = piles[j] + min(dp[i+1][j-1], dp[i][j-2]);

                dp[i][j] = max(v1, v2);
            }
        }
    }

    return dp[0][n-1];
}

```


## Stone Game 1
Alex and Lee play a game with piles of stones.  There are an even number of piles arranged in a row, and each pile has a positive integer number of stones piles[i].

The objective of the game is to end with the most stones. The total number of stones is odd, so there are no ties.

Alex and Lee take turns, with Alex starting first.  Each turn, a player takes the entire pile of stones from either the beginning or the end of the row.  This continues until there are no more piles left, at which point the person with the most stones wins.

Assuming Alex and Lee play optimally, return True if and only if Alex wins the game.

#### Test Case
Input: piles = [5,3,4,5]
Output: true

Explanation: 

Alex starts first, and can only take the first 5 or the last 5.
Say he takes the first 5, so that the row becomes [3, 4, 5].
If Lee takes 3, then the board is [4, 5], and Alex takes 5 to win with 10 points.
If Lee takes the last 5, then the board is [3, 4], and Alex takes 4 to win with 9 points.
This demonstrated that taking the first 5 was a winning move for Alex, so we return true.

#### Approach
What does it mean for Alex to win? Alex will win if score(Alex) >= score(Lee), but this also means score(Alex) - score(Lee) >= 0, so here you have a common parameter which is a score variable. 

The score parameter really means score = score(Alex) - score(Lee).

Now, if each player is suppoed to play optimally, how do you decide this with one variable?

Well since Alex is playing optimally, he wants to maximize the score variable because remember, Alex only wins if score = score(Alex) - score(Lee) >= 0 Alex should add to the score because he wants to maximize it.
Since Lee is also playing optimally, he wants to minimize the score variable, since if the score variable becomes negative, Lee has more individual score than Alex. But since we have only one variable, Lee should damage the score (or in other words, subtract from the score).

```cpp
class Solution {
public:
    vector<vector<v>> dp;
    
    int DFS(int s, int e, int player, vector<int> &piles) {
        if(s > e)
            return 0;
        
        if(dp[s][e][player] != -1)
            return dp[s][e][player];
        
        int ans = 0;
        int next = 1 - player;
        
        if(player == 1) {
            ans = max(piles[s] + DFS(s+1, e, next, piles), piles[e] + DFS(s, e-1, next, piles));
        }
        else {
            ans = min(-piles[s] + DFS(s+1, e, next, piles), -piles[e] + DFS(s, e-1, next, piles));
        }
        
        return dp[s][e][player] = ans;
    }
    
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        dp.resize(n, vector<v>(n, v(2, -1)));
        
        DFS(0, n-1, 1, piles);
        
        return dp[0][n-1][1];
    }
};

```



## Stone Game 3
Alice and Bob continue their games with piles of stones. There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array stoneValue.

Alice and Bob take turns, with Alice starting first. On each player's turn, that player can take 1, 2 or 3 stones from the first remaining stones in the row.

The score of each player is the sum of values of the stones taken. The score of each player is 0 initially.

The objective of the game is to end with the highest score, and the winner is the player with the highest score and there could be a tie. The game continues until all the stones have been taken.

Assume Alice and Bob play optimally.

Return "Alice" if Alice will win, "Bob" if Bob will win or "Tie" if they end the game with the same score.


#### TestCase
Input: values = [1,2,3,-9]
Output: "Alice"

Explanation: 

Alice must choose all the three piles at the first move to win and leave Bob with negative score.
If Alice chooses one pile her score will be 1 and the next move Bob's score becomes 5. The next move Alice will take the pile with value = -9 and lose.
If Alice chooses two piles her score will be 3 and the next move Bob's score becomes 3. The next move Alice will take the pile with value = -9 and also lose.
Remember that both play optimally so here Alice will choose the scenario that makes her win.


```cpp

    // space-time optimized

    string stoneGameIII(vector<int>& s) {
        int n = s.size();
        
        vector<int> suffix(n+1);
        suffix[n] = 0;
        for(int i=n-1; i>=0; i--)
            suffix[i] = suffix[i+1] + s[i];
        
        vector<int> dp(n+1);
        dp[n] = 0;
        
        for(int i=n-1; i>=0; i--) {
            dp[i] = INT_MIN;
            
            int cur = 0;
            for(int k=0; k<3 && i+k<n; k++) {
                cur += s[i+k];
                dp[i] = max(dp[i], cur + (suffix[i+k+1] - dp[i+k+1]));
            }
        }
        
        if(dp[0] * 2 == suffix[0])
            return "Tie";
        
        return (dp[0] * 2 > suffix[0])? "Alice": "Bob";
    }

    // classic Approach

    vector<vector<int>> dp;
    
    int DFS(vector<int> &s, int index, int M, int turn) {
        int n = s.size();
        
        if(index >= n) {
            return 0;
        }
        
        if(dp[index][turn] != -1)
            return dp[index][turn];
        
        int ans = INT_MIN, sum = 0;
        
        if(turn) {
            for(int i=index; i<index + M && i<n; i++) {
                sum += s[i];
                ans = max(ans, sum + DFS(s, i+1, M, 0));
            }
        } 
        
        else {
            ans = INT_MAX;
            for(int i=index; i<index + M && i<n; i++) {
                sum += s[i];
                ans = min(ans, -sum + DFS(s, i+1, M, 1));
            }   
        }
        
        return dp[index][turn] = ans;
    }
    
    string stoneGameIII(vector<int>& s) {
        int n = s.size();
        
        dp.resize(n, vector<int>(2, -1));
        
        DFS(s, 0, 3, 1);
        
        if(dp[0][1] == 0)
            return "Tie";
        
        return dp[0][1] > 0? "Alice": "Bob";
    }

```