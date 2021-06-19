/*"""
If the question says - Get the count of numbers whose digits sum is X in the range [L, R]
Brute Force method times out, Hence, a better method needs to be used.
DP on Digits is used for this purpose.

Here, DP[n, sum, tight] : digits left, sum left, tight constraint or not 

Tight constraint means whether we have an upperbound for the given digit or any digit can be chosen
Eg.

Num = 43562
    1. Initially its a tight constraint since the digit value >= 4 might result into a number with value > NUM
    2. For d = 1, 2, 3 here on moving to the next state, there is no tight constraint as the final num will always be less than NUM
    3. For d = 4, tight constraint moves to the next state.

"""
*/
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

ll dp[100][181][2];

ll solveDP(string &N, ll n, ll sum, bool tight){
    if(sum < 0) return 0;
    if(dp[n][sum][tight] != -1) return dp[n][sum][tight];
    if(n == 1){
        if(sum >= 0 && sum <= 9) return 1;
        return 0;
    }
    ll val = 0;

    int UB = (tight==1)? (N[N.length() - n] -'0') : 9;

    for(int i=0; i<=UB; i++){
        val += solveDP(N, n-1, sum-i, tight&(i == UB));
    }

    return dp[n][sum][tight] = val;
}

int main(){
    fast_io;
    string N; cin>>N;
    memset(dp, -1, sizeof(dp));

    ll ans = solveDP(N, N.length(), 15, 1);
    cout<<ans;
}