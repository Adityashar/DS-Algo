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

int find(vector<int> &p, int i){
    if(p[i] != i) p[i] = find(p, p[i]);
    return p[i];
}

void Union(vector<int> &p, int x, int y, vector<int> &sz){
    int xp = find(p, x), yp = find(p, y);
    if(xp != yp){
        if(xp > yp) p[xp] = yp, sz[yp] += sz[xp], sz[xp] = 0;
        else p[yp] = xp, sz[xp] += sz[yp], sz[yp] = 0;
    } 
}


int main(){
    fast_io;
    int t;
    cin>>t;
    rep(c, 0, t){
        ll A, Q;
        cin>>A;
        vector<pl> edges;
        unordered_map<pp, bool, hash_pair> map;
        for(int i=0; i<A-1; i++){
            int x, y;
            cin>>x>>y;
            edges.pb({x-1, y-1});
            map[{x-1, y-1}] = 1;
        }
        cin>>Q;
        vector<pl> queries;
        for(int i=0; i<Q; i++){
            int x, y;
            cin>>x>>y;
            queries.pb({x-1, y-1});
            map[{x-1, y-1}] = 0;
        }
        
        vector<int> p, sz;
        for(int i=0; i < A; i++) p.pb(i), sz.pb(1);
        for(int i=0; i<A-1; i++){
            int xb = edges[i].first, yb = edges[i].second;
            if(map[{xb, yb}] == 1) Union(p, xb, yb, sz);
        }
        int ans = -1;
        for(int i: sz) cout<<i<<" ", ans = max(ans, i); cout<<endl;
        vector<int> a;
        a.pb(ans);
        rev(queries);
        for(int i=0; i<Q-1; i++){
            int x = queries[i].first, y = queries[i].second;
            Union(p, x, y, sz);
            ans = max(ans, sz[find(p, x)]);
            for(int i: sz) cout<<i<<" "; cout<<endl;
            // cout<<find(p, x)<<endl;
            a.pb(ans);
        }
        for(int i: a) cout<<i<<" ";
    }
}