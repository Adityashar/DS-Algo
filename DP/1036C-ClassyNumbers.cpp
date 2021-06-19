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

ll dp[20][2][20];

ll solve(string &S, int n, bool ti, int k){
    ll ans = 0;
    ll &ref = dp[n][ti][k];

    if(ref != -1) return ref;

    if(n == 0){
        return ref = (k <= 3);
    }

    int ub = ti==1? (S[S.length() - n] -'0'): 9;

    for(int i=0; i<= ub; i++){
        if(k > 3 && i == 0){
            ans += solve(S, n-1, ti&(i == ub), k);
        }
        else{
            ans += solve(S, n-1, ti&(i == ub), k + (i != 0));
        }
    }

    return ref = ans;
}

int main(){
    fast_io;
    int t;
    cin>>t;
    rep(c, 0, t){
        ll l, r;
        cin>>l>>r;
        string L = to_string(l-1), R = to_string(r);

        memset(dp, -1, sizeof(dp));
        ll ansR = solve(R, R.length(), 1, 0);

        memset(dp, -1, sizeof(dp));
        ll ansL = solve(L, L.length(), 1, 0);

        cout<<ansR - ansL<<endl;

    }
}