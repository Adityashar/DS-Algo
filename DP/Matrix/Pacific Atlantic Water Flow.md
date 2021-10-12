# 417. Pacific Atlantic Water Flow

There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the island's right and bottom edges.

The island is partitioned into a grid of square cells. You are given an m x n integer matrix heights where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).

The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is less than or equal to the current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.

Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.

Input: 
heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]

Output: 
[[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]

```cpp
// 70ms

vector<vector<int>> visited;
vector<vector<int>> ans;

int n, m;

void DFS(vector<vector<int>>& h, int r, int c, int label) {
    if(visited[r][c] == label || visited[r][c] == 3)
        return;
    
    visited[r][c] += label;
    
    if(visited[r][c] == 3)
        ans.push_back({r, c});
    
    int x[] = {-1, 1, 0, 0}, y[] = {0, 0, 1, -1};
    
    for(int i=0; i<4; i++) {
        int nx = x[i] + r, ny = y[i] + c;
        
        if(nx >= 0 && ny < m && nx < n && ny >= 0 && h[r][c] <= h[nx][ny])
            DFS(h, nx, ny, label);
    }
}

vector<vector<int>> pacificAtlantic(vector<vector<int>>& h) {
    n = h.size();
    m = h[0].size();
    
    visited.resize(n, vector<int>(m, 0));
    
    for(int i=0; i<n; i++) {
        DFS(h, i, 0, 1);
        DFS(h, i, m-1, 2);
    }
    
    for(int i=0; i<m; i++) {
        DFS(h, 0, i, 1);
        DFS(h, n-1, i, 2);
    }
    
    return ans;
}



// 200 ms
#define pp pair<int,int>
#define f first
#define s second

class Solution {
public:
    int n, m;
    vector<vector<pp>> dp;
    vector<vector<bool>> v;
    
    pp DFS(vector<vector<int>>& g, int r, int c, int prev) {
        
        if(r < 0 || c < 0)
            return {1, 0};
        
        if(r == n || c == m)
            return {0, 1};
        
        if(v[r][c] == true || g[r][c] > prev)
            return {0, 0};
        
        if(dp[r][c].f == 1 && dp[r][c].s == 1)
            return dp[r][c];
        
        pp ans = {0, 0};
        int x[] = {0,0,-1,1}, y[] = {-1,1,0,0};
        
        v[r][c] = 1;
        
        for(int i=0; i<4; i++) {
            int nx = x[i] + r, ny = y[i] + c;
            
            pp val = DFS(g, nx, ny, g[r][c]);
            ans.f |= val.f, ans.s |= val.s; 
        }
        
        v[r][c] = 0;
        
        return dp[r][c] = ans;
    }
    
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& g) {
        n = g.size();
        m = g[0].size();
        
        dp.resize(n, vector<pp>(m, {-1, -1}));
        v.resize(n, vector<bool>(m, 0));
        
        vector<vector<int>> ans;
        
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {    
                DFS(g, i, j, INT_MAX);
            
                if(dp[i][j].f == 1 && dp[i][j].s == 1)
                    ans.push_back({i, j});
            }
        }

        return ans;
    }
};

```