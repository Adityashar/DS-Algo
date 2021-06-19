1162. As Far from Land as Possible


class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int level = 0, n = grid.size();
        vector<vector<int>> visited(n, vector<int>(n, 0));
        queue<pair<int, int>> q;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(grid[i][j]){
                    q.push({i, j}); visited[i][j] = 1;
                }
                else visited[i][j] = 0;
            }
        }
        int s = q.size();
        if(s == 0 || s == n*n) return -1;
        while(q.empty() == 0){
            int s = q.size();
            while(s--){
                int i = q.front().first, j = q.front().second;
                q.pop();
                
                int x[] = {-1, 1, 0, 0}, y[] = {0, 0, -1, 1};
                for(int k=0; k<4; k++){
                    int xnew = i + x[k], ynew = j + y[k];
                    if(xnew >= 0 && xnew < n && ynew >=0 && ynew < n && visited[xnew][ynew] == 0){
                        visited[xnew][ynew] = 1;
                        q.push({xnew, ynew});
                    }
                }
            }
            if(q.size() == 0) break;
            level++;
        }
        
        return level;
    }
};