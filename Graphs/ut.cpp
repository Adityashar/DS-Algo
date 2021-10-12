#include<bits/stdc++.h>
using namespace std;

#define pp pair<int, int>
#define ps pair<pp, string>
#define f first
#define s second


vector<vector<int>> shortestPath(vector<vector<int>> &grid) {
	int n = grid.size();
	int m = grid[0].size();

	vector<vector<int>> level(n, vector<int>(m, -1));

	queue<pp> q;
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(grid[i][j] == 1)
				q.push({i, j}), level[i][j] = 0;
		}
	}

	int l = 1;

	while(q.size() > 0) {
		int s = q.size();

		while(s--) {
			pp cur = q.front(); 
			q.pop();

			int x[] = {-1,1,0,0}, y[] = {0,0,1,-1};
			int val[] = {3, 2, 4, 5};

			for(int k = 0; k < 4; k++) {
				int nx = x[k] + cur.f, ny = y[k] + cur.s;

				if(nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] != -1 && grid[nx][ny] != 1) {
					if(grid[nx][ny] == 0) {
						grid[nx][ny] = val[k];
						level[nx][ny] = l;
						q.push({nx, ny});
					}
					else if(level[nx][ny] == l && grid[nx][ny] > val[k]){
						grid[nx][ny] = val[k];
					}
				}
			} 
		}
		l++;
	}

	return grid;
}


int main() {

	vector<vector<int>> M = {{1,0,1}, {0,0,0}, {1,0,0}};
	
	vector<vector<int>> ans = shortestPath(M);

	for(auto i: ans) {
		for(auto j: i)
			cout<<j<<" ";
		cout<<endl;
	}

	return 0;
}