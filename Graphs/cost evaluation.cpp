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

struct Edges{
    int x, y;
};

int find(int x, vector<int> &p){
    if(p[x] != x) p[x] = find(p[x], p);
    return p[x];
}

void un(int x, int y, vector<int> &p, vector<int> &sz){
    int xp = find(x, p), yp = find(y, p);
    if(xp == yp) return;
    p[yp] = xp;
    sz[xp] += sz[yp];
    sz[yp] = 0;    
}

int main(){
    fast_io;
    int n, e;
    cin>>n>>e;
    vector<int> p, size;
    rep(i, 0, n){
        p.pb(i), size.pb(1);
    }
    Edges *E = new Edges[e];

    rep(i, 0, e){
        int x, y;
        cin>>x>>y;
        E[i].x = x, E[i].y = y;
    }     
    rep(i, 0, e){
        un(E[i].x, E[i].y, p, size);
    }
    int ans = 0;
    // for(int ep: p) cout<<ep<<" ";
    // cout<<endl;
    for(int ep: size) ans += ceil(sqrt(ep));
    cout<<ans;
}