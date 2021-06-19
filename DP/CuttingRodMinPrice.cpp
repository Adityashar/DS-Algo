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

void print2D(vector<vector<int>> &v){
    for(int i=0; i<v.size(); i++){
        cout<<i<<" : ";
        for(int j=0; j<v[i].size(); j++) cout<<v[i][j]<<" ";
        cout<<endl;
    }
}



ll solve(vector<ll> &v, int s, int e, int x, int y, vector<vector<int>> &dp){
    ll val = INT_MAX;
    
    if(s == e - 1 || s == e){
        dp[s][e] = 0;
        return 0;
    }
    if(dp[s][e] != -1) return dp[s][e];
    if(s + 2 == e){
        dp[s][e] = x*(v[s+1] - v[s]) + y*(v[e] - v[s+1]); 
        return dp[s][e];
    }
    
    int L = v[e], S = v[s];

    for(int i=s+1; i<e; i++){
        ll cur = x*(v[i] - S) + y*(L - v[i]);
        cur += solve(v, s, i, x, y, dp) + solve(v, i, e, x, y, dp);
        val = min(val, cur);
    }
    return dp[s][e] = val;
}

int main(){
    ll t, m;
    cin>>t;
    rep(c, 0, t){
        int x, y, n; 
        cin>>x>>y;
        cin>>n;
        vector<vector<int>> dp(n, vector<int>(n, -1));
        vector<ll> v;
        rep(i, 0, n){
            int x1; cin>>x1; v.pb(x1);
        }
        ll ans = solve(v, 0, n-1, x, y, dp);
        cout<<ans<<endl;
    } 
}