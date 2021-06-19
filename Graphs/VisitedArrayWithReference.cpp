#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fr(a,b) for(int i = a; i < b; i++)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define mod 998244353 
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

void print2D(vector<vector<ll>> &v){
    for(int i=0; i<v.size(); i++){
        cout<<i<<" : ";
        for(int j=0; j<v[i].size(); j++) cout<<v[i][j]<<" ";
        cout<<endl;
    }
}

void dfs(vector<vector<ll>> &adj, vector<ll> &v, ll root, ll cats_till_now, ll &ans, ll k, vector<bool> &visited){
    ll m = adj[root].size();
    // visited[root] = true;
    if(m == 1 && visited[adj[root][0]]){
        if(cats_till_now <= k) ans += 1;
        return;
    }
    for(ll i=0; i<m; i++){
        ll neigh = adj[root][i];
        if(!visited[neigh] && cats_till_now + v[neigh] <= k){
            visited[neigh] = true;
            dfs(adj, v, neigh, (v[neigh] == 0)? 0: cats_till_now + 1, ans, k, visited);
            visited[neigh] = false;
        }
    }
}

int main(){
    fast_io;
    int t;
    // cin>>t;
    // rep(c, 0, t){
        ll n, k, p;
        vector<ll> v;
        cin>>n>>k;
        vector<vector<ll>> adj(n);
        rep(i, 0, n) cin>>p, v.pb(p);
        rep(i, 0, n-1){
            int x, y;
            cin>>x>>y;
            adj[y-1].pb(x-1);
            adj[x-1].pb(y-1);
        }
        // print2D(adj);
        ll ans = 0;
        vector<bool> visited(n, 0);
        visited[0] = true;
        if(k == 0 && v[0] == 1) ans = 0;
        else dfs(adj, v, 0, v[0], ans, k, visited);
        cout<<ans<<endl;
    // }
}
// 12 3
// 1 0 1 0 1 1 1 1 0 0 0 0
// 6 7
// 12 1
// 9 7
// 1 4
// 10 7
// 7 1
// 11 8
// 5 1
// 3 7
// 5 8
// 4 2