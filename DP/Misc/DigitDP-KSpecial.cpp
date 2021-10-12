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

int LCM = 2520, K;
ll dp[20][2][2520][(1<<9) + 3];
string S;

ll solve(int n, bool tight, int mask, int rem){
    //
    if(dp[n][tight][rem][mask] != -1) 
        return dp[n][tight][rem][mask];

    if(n == 0){
        int cnt = 0;
        rep(i, 1, 10){
            if((mask & (1<<(i-1))) && (rem % i == 0)) 
                cnt++;
        }    
        if(cnt >= K) return dp[n][tight][rem][mask] = 1;
        else return dp[n][tight][rem][mask] = 0;
    }
    //

    ll ans = 0;
    int UB = tight == 1? (S[S.length() - n] - '0'): 9;

    for(int i=0; i<=UB; i++){
        mask = i == 0? mask: mask|(1<<(i-1));
        rem = (rem * 10 + i) % LCM;
        ans += solve(n-1, tight&(i==UB), mask, rem);
    }
    return dp[n][tight][rem][mask] = ans;
}

int main(){
    fast_io;
    int t;
    cin>>t;
    rep(c, 0, t){
        ll l, r; int k;
        cin>>l>>r>>k;
        string L = to_string(l-1), R = to_string(r);
        K = k;        
        // cout<<L<<" "<<R;
        memset(dp, -1, sizeof(dp));
        S = R;
        ll ansR = solve(R.length(), 1, 0, 0);
        
        S = L;
        memset(dp, -1, sizeof(dp));
        ll ansL = solve(L.length(), 1, 0, 0);
        
        cout<<ansR - ansL<<endl;
    }
}
