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
using namespace std;


int subtree(int root, vector<vector<int>> &adj, int &ans, vector<int> &v){
    int val = 0;
    for(int i=0; i<adj[root].size(); i++){
        val += subtree(adj[root][i], adj, ans, v);
    }
    if(v[root] & 1) val = 0;
    else val++;
    
    ans = max(ans, val);
    return val;
}

int main(){
    fast_io;
    int n = 7;
    // cin>>n; 
    vector<int> v = {0, 1 , 6, 4, 2, 0, 3};
    // rep(i, 0, n) int k, cin>>k, v.pb(k);
    vector<pp> edge = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {3, 5}, {5, 6}};
    // int x, y;
    // rep(i, 0, n-1) cin>>x>>y, edge.pb({x, y});

    vector<vector<int> > adj(n);
    for(int i=0; i<n-1; i++){
        int x = edge[i].first, y = edge[i].second;
        if(x < y) adj[x].pb(y);
        else adj[y].pb(x);
    }

    int root = 0, ans = 0;
    int maxSubtree = subtree(root, adj, ans, v);

    cout<<ans<<endl;

}