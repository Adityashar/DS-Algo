
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

bool comp(pair<pl, ll> &A, pair<pl, ll> &B){
    if(A.second < B.second) return 1;
    else return 0;
}

vector<pair<pl, ll>> edges;

int find(vector<ll> &p, ll i){
    if(p[i] != i) p[i] = find(p, p[i]);
    return p[i];
}

unordered_map<ll, ll> mapp;

// """
// when performing union of x and y,
// the subtree size of x becomes x + y 
// and the subtree size of y becomes 0
// since y is now a part s subtree.

// During this union, the change in pairs should be calculated and added to the total number of pairs in a subtree having 
// max weight edge as w.
// """

void Union(vector<ll> &p, ll x, ll y, vector<ll> &sz, ll w){
    int xc = find(p, x), yc = find(p, y);
    
    if(xc == yc) return;

    ll xsize = sz[xc], ysize = sz[yc], sum;

    p[yc] = xc;
    sz[xc] += ysize;
    sz[yc] = 0;

    sum = sz[xc]*(sz[xc]-1) - xsize*(xsize-1) - ysize*(ysize-1);

    mapp[w] += sum/2;

    return;
}


int main(){
    fast_io;

// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif

    ll n,Q; cin>>n>>Q;
    vector<ll> parent;

    for(int i=0; i<n; i++) parent.pb(i);

    ll x, y;

    vector<bool> eb;
    for(int i=0; i<n-1; i++){
        ll z;
        cin>>x>>y>>z;
        edges.pb({{x-1, y-1}, z});
    }

    sort(edges.begin(), edges.end(), comp);
    vector<ll> sz(n, 1);

    for(auto e: edges){
        ll x = e.first.first, y = e.first.second, w = e.second;
        Union(parent, x, y, sz, w);
    }

    // for(auto i: edges) cout<<i.second<<" ";

    vector<pl> queries;
    for(int i=0; i<Q; i++) cin>>x>>y, queries.pb({x, y}); 

    vector<ll> keys;
    for(auto ip: mapp) keys.pb({ip.first});
    sort(keys.begin(), keys.end());
    ll k = keys.size();
    vector<ll> pre(k);
    pre[0] = (mapp[keys[0]]);

    for(int i=1; i<k; i++){
        pre[i] = pre[i-1] + mapp[keys[i]];
        mapp[keys[i]] = pre[i];
    }

    repMAP(mapp, it){
        cout<<it->first<<" "<<it->second<<endl;
    }

    for(pl q: queries){
        ll l = q.first, r = q.second;
        ll lb = *(lower_bound(keys.begin(), keys.end(), l) - 1);
        ll ub = *(upper_bound(keys.begin(), keys.end(), r) - 1);
        cout<<mapp[ub] - mapp[lb]<<endl;
    }
    
    return 0;
}