// https://math.stackexchange.com/questions/2872647/for-each-edge-in-a-tree-counting-paths-passing-through-this-edge

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
using namespace std;



vector<pl> edges;

int find(vector<int> &p, int i){
    if(p[i] != i) p[i] = find(p, p[i]);
    return p[i];
}
void Union(vector<int> &p, int x, int y){
    int xc = find(p, x), yc = find(p, y);
    if(xc != yc){
        p[yc] = xc;
    }
}

void dfs(vector<vector<pl>> &adj, vector<ll> &subtree, ll root){
    int m = adj[root].size();

    for(int i=0; i<m; i++){
        ll neigh = adj[root][i].first;
        dfs(adj, subtree, neigh);
        subtree[root] += subtree[neigh]; 
    }
}

int main(){
    fast_io;

// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif

    ll n,Q; cin>>n>>Q;
    vector<ll> parent;
    vector<ll> weight;
    vector<vector<pl>> adj(n);

    for(int i=0; i<n; i++) parent.pb(i);

    ll x, y;

    vector<bool> eb;
    for(int i=0; i<n-1; i++){
        ll z;
        cin>>x>>y>>z;
        edges.pb({x-1, y-1});  
        weight.pb(z);
        adj[x-1].pb({y-1, z});
    }

    vector<ll> subtreeSize(n, 1);
    vector<ll> ans;
    dfs(adj, subtreeSize, 0);

    for(int i=0; i<n-1; i++){
        ll val = subtreeSize[edges[i].second] * (n - subtreeSize[edges[i].second]);
        ans.pb(val);  
    }
    for(int i: ans) cout<<i<<" ";
    // vector<pl> queries;
    // for(int i=0; i<Q; i++) cin>>x>>y, queries.pb({x-1, y-1}); 

    
    
}