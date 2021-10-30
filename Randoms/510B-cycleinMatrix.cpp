#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fr(a,b) for(int i = a; i < b; i++)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define mod 1000000007 
#define inf (1LL<<60)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define triplet pair<ll,pair<ll,ll>>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define pl pair<ll, ll> 
#define pp pair<int, int>
#define rev(str) reverse(str.begin(), str.end())
#define repMAP(map, it) for(auto it = map.begin(); it != map.end(); it++)
#define begEnd(it) it.begin(), it.end()
#define sort(v) sort(v.begin(), v.end())
using namespace std;

struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
};

vector<vector<char>> mat;
vector<vector<int>> v, rs;

bool DFS(int r, int c, char col, int pr, int pc) {
    int n = mat.size();
    int m = mat[0].size();

    v[r][c] = 1;
    rs[r][c] = 1;

    int x[] = {1,-1,0,0}, y[] = {0,0,1,-1};

    for(int k=0; k<4; k++) {
        int nx = x[k] + r, ny = y[k] + c;

        if(nx >= 0 && ny >= 0 && nx < n && ny < m && col == mat[nx][ny]) {
            if(pr == nx && pc == ny)
                continue;
            
            if(!v[nx][ny] && DFS(nx, ny, col, r, c))
                return true;
            
            if(rs[nx][ny])
                return true;
        }
    }

    rs[r][c] = 0;

    return false;
}



int main() {
    fast_io;

    int n, m; 
    cin>>n>>m;

    v.resize(n, vector<int>(m, 0));
    rs.resize(n, vector<int>(m, 0));
    mat.resize(n, vector<char>(m));

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            char x;
            cin>>x;

            mat[i][j] = x;
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(!v[i][j] && DFS(i, j, mat[i][j], -1, -1)) {
                // cout<<i<<" "<<j<<endl;
                cout<<"YES";
                return 0;
            }
        }
    }

    cout<<"NO";

    return 0;
}