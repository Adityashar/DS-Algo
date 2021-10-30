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
#define f first
#define s second
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

/*

    MEX ->

    Smallest positive integer not a part of that set of integers

    if for a node with degree >= 2 i.e no. of edges >= 2
    
    then assigning the edges as 0, 1, 2 ensures that no path in the tree will have 0, 1, 2 in the single UtoV path

    and hence the max MEX for all paths within the tree will become atmost 2.

*/


// make a mapping of vertices to the edges that belong to them
vector<vector<int>> adj;

int main() {
    fast_io;

    int n;
    cin>>n;

    vector<int> res(n-1, -1);
    int val = 0;

    adj.resize(n);

    for(int i=0; i<n-1; i++) {
        int x, y; cin>>x>>y;

        adj[x-1].pb(i);
        adj[y-1].pb(i);
    }

    for(int i=0; i<n; i++) {
        if(adj[i].size() > 2) {
            res[adj[i][0]] = 0;
            res[adj[i][1]] = 1;
            res[adj[i][2]] = 2;

            val = 3;

            break;
        } 
    }

    for(auto &i: res) {
        if(i == -1) {
            i = val++;
        }
    }

    for(auto i: res)
        cout<<i<<endl;

    return 0;
}
