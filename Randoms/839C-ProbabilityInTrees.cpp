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

vector<vector<int>> adj;

double DFS(int r, int p, int depth, double prob) {
    double ans = 0.0;
    double size = adj[r].size() - (p != -1);

    for(auto i: adj[r]) {
        if(i == p)
            continue;
        
        double cur_prob = 1.0 / size;
        ans += DFS(i, r, depth+1, prob * cur_prob);
    }

    if(adj[r].size() == 1 && adj[r][0] == p)
        ans += depth * prob;

    return ans;
}

int main() {
    fast_io;

    int n;
    cin>>n;

    adj.resize(n);

    for(int i=0; i<n-1; i++) {
        int x, y; cin>>x>>y;

        adj[x-1].pb(y-1);
        adj[y-1].pb(x-1); 
    }

    double ans = DFS(0, -1, 0, 1.0);

    cout<<fixed<<setprecision(6)<<ans;

    return 0;
}
