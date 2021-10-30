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
#define pd pair<int, vector<int>> 
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

struct comp {
    bool operator() (pd &p1, pd &p2) {
        if(p1.s.size() != p2.s.size())
            return p1.s.size() < p2.s.size();
        
        return p1.first > p2.first;
    }
};



int main() {
    fast_io;
    
    int t;
    cin>>t;

    while(t--) {
        int n, m;
        cin>>n>>m;

        vector<vector<int>> adj;

        adj.resize(n);

        for(int i=0; i<m; i++) {
            int x, y; cin>>x>>y;

            adj[x-1].pb(y-1);
            adj[y-1].pb(x-1);
        }

        priority_queue<pd, vector<pd>, comp> pq;

        // for(auto i: adj) {
        //     for(auto j: i)
        //         cout<<" - "<<j<<" - ";
        //     cout<<endl;
        // }

        for(int i=0; i<n; i++)
            pq.push({i, adj[i]});

        vector<int> res;
        vector<int> visited(n, 0);

        while(pq.size() > 0) {
            pd top = pq.top(); pq.pop();

            // cout<<" - "<<top.f<<" - "<<visited[top.f]<<" - ";

            // for(auto i: top.s)
            //     cout<<i<<" ";

            // cout<<endl;

            if(visited[top.f])
                continue;

            res.pb(top.f + 1);
            visited[top.f] = 1;

            for(auto i: top.s) {
                if(visited[i] == 0) {
                    visited[i] = 1;
                }
            }
        }

        cout<<res.size()<<endl;
        for(auto i: res)
            cout<<i<<" ";
        
        cout<<endl;
    }

    return 0;
}
