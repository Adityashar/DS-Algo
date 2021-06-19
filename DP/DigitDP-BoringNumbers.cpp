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

ll dp1[20][2][2][2];
ll dp2[20][2][2][2];

ll solveDP1(string &N, ll n, bool even, bool leading, bool tight){
    if(n == 0) return 1;
    if(dp1[n][even][leading][tight] != -1) return dp1[n][even][leading][tight];

    if(even){
        ll ans = 0;
        vector<int> d = {0, 2, 4, 6, 8};

        int ub = (tight == 1) ? (N[N.length() - n] - '0'): 9;
        for(int digit : d){
            if(digit <= ub ){
                ans += solveDP1(N, n-1, 0, 0, tight&(ub==digit));
            }
        }
        return dp1[n][even][leading][tight] = ans;
    }
    else{
        ll ans = 0;
        vector<int> d = {1, 3, 5, 7, 9};

        if(leading){
            ans += solveDP1(N, n-1, 0, 1, 0);
        }

        int ub = (tight == 1) ? (N[N.length() - n] - '0'): 9;
        for(int digit : d){
            if(digit <= ub ){
                ans += solveDP1(N, n-1, 1, 0, tight&(ub==digit));
            }
        }
        return dp1[n][even][leading][tight] = ans;
    }
}


ll solveDP2(string &N, ll n, bool even, bool leading, bool tight){
    if(n == 0) return 1;
    if(dp2[n][even][leading][tight] != -1) return dp2[n][even][leading][tight];

    if(even){
        ll ans = 0;
        vector<int> d = {0, 2, 4, 6, 8};

        int ub = (tight == 1) ? (N[N.length() - n] - '0'): 9;
        for(int digit : d){
            if(digit <= ub ){
                ans += solveDP2(N, n-1, 0, 0, tight&(ub==digit));
            }
        }
        return dp2[n][even][leading][tight] = ans;
    }
    else{
        ll ans = 0;
        vector<int> d = {1, 3, 5, 7, 9};

        if(leading){
            ans += solveDP2(N, n-1, 0, 1, 0);
        }

        int ub = (tight == 1) ? (N[N.length() - n] - '0'): 9;
        for(int digit : d){
            if(digit <= ub ){
                ans += solveDP2(N, n-1, 1, 0, tight&(ub==digit));
            }
        }
        return dp2[n][even][leading][tight] = ans;
    }
}

int main(){
    fast_io;
    int t; cin>>t;
    rep(c, 0, t){
        ll r, l; 
        cin>>l>>r;
        l--;
        string R = to_string(r), L = to_string(l);
        memset(dp1, -1, sizeof(dp1));
        memset(dp2, -1, sizeof(dp2));

        cout<<"Case #"<<c + 1<<": "<<solveDP1(R, R.length(), 0, 1, 1) - solveDP2(L, L.length(), 0, 1, 1)<<endl;
    }
}