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

int main(){
    fast_io;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ll n; cin>>n;
    vector<int> parent;
    vector<bool> black;

    for(int i=0; i<n; i++) parent.pb(i), black.pb(0);

    vector<bool> eb;
    for(int i=0; i<n-1; i++){
        int x, y; char c;
        cin>>x>>y>>c;
        int z = c == 'b'? 1 : 0;
        eb.pb(z);
        if(z == 1){
            black[x-1] = black[y-1] = 1;
            Union(parent, x-1, y-1);
        }
        edges.pb({x-1, y-1});      
    }

    // for(int i: parent) cout<<i<<" ";
    // cout<<endl;
    vector<int> cnt(n, 0);
    for(int i: parent){
        cnt[find(parent, i)]++;
    }
    // for(int i: cnt) cout<<i<<" ";
    // cout<<endl;
    ll ans = (n * (n-1) * (n-2));
    // cout<<ans<<" ";
    for(int t=0; t<n; t++){
        ll val = 0, i = cnt[t];
        if(i > 1 && black[t]){
            val = ((3*n - 2*i - 2)*(i - 1)*(i));
            // cout<<val<<" ";
        }
        ans -= val;
    }

    cout<<(ans/6)%mod;
}