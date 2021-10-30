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



vector<int> cat;
vector<vector<int>> adj;


int DFS(int root, int streak, int m, int p) {
    int ans = 0;

    for(auto i: adj[root]) {
        if(i == p) {
            continue;
        }

        if(cat[i] == 0)
            ans += DFS(i,  0, m, root);
        else if(streak + 1 <= m) {
            ans += DFS(i, streak + 1, m, root);
        }
    }

    ans += (adj[root].size() == 1) && (adj[root][0] == p);

    return ans;
}

int main() {
    fast_io;

    int n, m;
    cin>>n>>m;

    adj.resize(n);

    for(int i=0; i<n; i++) {
        int x; cin>>x;

        cat.pb(x);
    }

    for(int i=0; i<n-1; i++) {
        int x, y; cin>>x>>y;

        adj[x-1].pb(y-1);
        adj[y-1].pb(x-1);
    }

    int ans = DFS(0, cat[0], m, -1);
    
    cout<<ans;

    return 0;
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