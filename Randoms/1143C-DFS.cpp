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

vector<set<int>> adj;
vector<int> c, ans;

bool check(int root) {

    for(auto i: adj[root])
        if(c[i] == 0)
            return false;

    return true;
}

void DFS(int root, int parent) {
    int np = root;

    if(c[root] && check(root)) {
        ans.pb(root+1);
        np = parent;
    }

    for(auto i: adj[root]) {
        if(i != parent) {
            DFS(i, np);
        }
    }

}

int main() {
    fast_io;

    int n; 
    cin>>n;

    adj.resize(n);
    c.resize(n);

    int root = -1;

    for(int i=0; i<n; i++) {
        int x, y;
        cin>>x>>y;

        c[i] = y;
        
        if(x != -1)
            adj[x-1].insert(i);
        else
            root = i; 
    }

    DFS(root, -1);

    sort(ans);

    if(ans.size() == 0)
        cout<<"-1";   

    else {
        for(auto i: ans)
            cout<<i<<" ";
    }

    return 0;
}